/* sweepy.inc */

  idur     = p3
  ibegfreq = 1 ; bgng of sweep freq
  iendfreq = p4*2 ; ending of sweep frequency
  ibw      = 70  ; bandwidth of filters in Hz
  ifreq    = 200 ; frequency of gbuzz that is to be filtered
  iamp     = (p5/127)*2 ; amplitude to scale output by
  ires     = 1 ; coefficient to scale amount of reson in output
  iresr    = 1 ; coefficient to scale amount of resonr in output
 ; Frequency envelope for reson cutoff
  kfreq    linseg ibegfreq, idur * .5, iendfreq, idur * .5, ibegfreq
 ; Amplitude envelope to prevent clicking
  kenv     linseg 0, .05, iamp, idur - .1, iamp, .05, 0
  iharms   = (sr*.4)/ifreq  ; Num of harmonics for gbuzz scaled to avoid aliasing
  asig     gbuzz 1, ifreq, iharms, 1, .9, 1 ; "Sawtooth" waveform
  ain      = kenv * asig  ; output scaled by amp envelope
  ares     reson ain, kfreq, ibw, 1
  aresr    resonr ain, kfreq, ibw, 1
  iampRrnd random 0.1, 0.9
  iampR =   1 - iampRrnd

aoutL init 0
aoutR init 0  
;reson Left
aoutL = ares * ires
;resonr Right 
aoutR = aresr * iresr * iampR
outs aoutL, aoutR