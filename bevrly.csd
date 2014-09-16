<CsoundSynthesizer>
<CsOptions>
-odac
</CsOptions>
<CsInstruments>

sr = 44100
ksmps = 128
nchnls = 2
0dbfs = 1.0

; Include user-defined opcodes
#include "includes/sendOpcodes.inc"
; Include the file with all the various tables
#include "includes/suntables.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; G L O B A L S
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

gievenon	= 1
gioddon  	= 1

gi01on 		= 1     *gioddon 		/* i1 sco is  */
gi02on 		= 1     *gievenon 		/* i2 sco is  */
gi03on 		= 1     *gioddon 		/* i3 sco is  */
gi04on 		= 1     *gievenon		/* i4 sco is  */
gi05on 		= 1     *gioddon		/* i5 sco is  */

giamp   = 0.01 			; base volume control
gi01amp = giamp + 0.1
gi02amp = giamp
gi03amp = giamp
gi04amp = giamp
gi05amp = giamp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; I N S T R U M E N T   D E F I N I T I O N S
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Include the mixer instruments
#include "instruments/busseffects.inc"

instr sweepy 
	#include "instruments/sweepy.inc"
endin
instr swave 
	#include "instruments/swave.inc"
endin

instr borrowedphazor ; 
 iamp 		= 100/127
 iendamp 	= 100/(127*3)
 inote 		= p4
 ipsix 		= 0.001
 ipsev 		= 0.005
 k1 linen iamp,ipsix,iendamp,ipsev
 a9 phasor inote, 			p4
 a8 phasor inote, 			p4*.7
 a7 phasor inote, 			p4*.98
 a6 phasor inote*0.99, 	0
 a5 phasor inote*0.98, 	0
 a4 phasor inote*0.97, 	0
 a3 phasor inote*0.96, 	0
 a2 phasor inote*0.95, 	0
 a1 phasor inote*0.9, 	0
 a11 = a1 * a2 * a3 * a4 * a5 * a6 + (a7 * a8 * a9)*.9
 ;a10 butterhp a11, 10
 out a11*k1, a11*k1
endin     
                        

instr tootfour
	iamp = 100/127       
	iscale = iamp * .2       ; scale the amp at initialization
	inote = p4         ; convert octave.pitch to cps
	iatt = 0.05
	irel = 0.1
	
	k1 linen iscale, iatt, p3, irel  ; p4=amp
	
	a3 oscil k1, inote*.996, 1   
	a2 oscil k1, inote*1.004, 1  
	a1 oscil k1, inote, 1        
	
	a1 = a1+a2+a3
	;outs a1, a1

endin

instr tootjr
	iamp = 100/127       
	iscale = iamp * .2       ; scale the amp at initialization
	inote = p4         ; convert octave.pitch to cps
	iatt = 0.05
	irel = 0.1
	
	k1 linen iscale, iatt, p3, irel  ; p4=amp
	
	a6 oscil k1, inote*0.75, 1   
	a5 oscil k1, inote*0.8, 1  
	a4 oscil k1, inote*0.9, 1 
	a3 oscil k1, inote*0.996, 1   
	a2 oscil k1, inote*1.004, 1  
	a1 oscil k1, inote, 1  
	apulse mpulse k1, 0.001      
	
	aout = (a1+a2+a3+a4+a5+a6)*apulse
	outs aout, aout

endin

instr resonz
; i1  0 0.136508 1 3000 200 100 4000 1 0 0   
  idur     =        p3
  ibegfreq =        p4          	; beginning of sweep frequency
  iendfreq =        3000 + p5   	; ending of sweep frequency
  ibw      =        600         	; bandwidth of filters in Hz
  ifreq    =        100 ; p7		; frequency of gbuzz that is to be filtered
  iamp     =        0.5 ; p8 ; amplitude to scale output by
  ires     =        0.1 ; p9    ; coef to scale amount of reson in output
  iresr    =        0 ; p10   ; coefnt to scale amount of resonr in output
  iresz    =        0.1 ; p11 	 ; coefnt to scale amount of resonz in output
  
 ; Frequency envelope for reson cutoff
  kfreq    linseg ibegfreq, idur * .5, iendfreq, idur * .5, ibegfreq
  
 ; Amplitude envelope to prevent clicking
  kenv     linseg 0, .1, iamp, idur - .2, iamp, .1, 0
  
 ; Number of harmonics for gbuzz scaled to avoid aliasing
  iharms   =        (sr*.4)/ifreq
  
  asig     gbuzz 1, ifreq, iharms, 1, .9, 1      ; "Sawtooth" waveform
  ain      =        kenv * asig                     ; output scaled by amp envelope
  ares     reson ain, kfreq, ibw, 1
  aresr    resonr ain, kfreq, ibw, 1
  aresz    resonz ain, kfreq, ibw, 1
  
           out ares * ires + aresr * iresr + aresz * iresz
  
endin

instr 1 
   	idur	= p3
	ipitch 	= p4
	ivel 	= p5
	#include "instruments/swave-without-outs.inc"
	if (gi01on==1) then  
		AssignSend		        p1, 0.025, 0.5, gi01amp
		SendOut			        p1, aout, aout
	endif
endin ; end ins 1
instr 2 
	ipitch = p4
	ivel 	= p5
	aSubOutL, aSubOutR subinstr "swave", ipitch
	if (gi02on==1) then  
		AssignSend		        p1, 0.25, 0.1, gi02amp
		SendOut			        p1, aSubOutL, aSubOutR
	endif
endin ; end ins 2
instr 3 
	ipitch = p4
	ivel 	= p5
	aSubOutL, aSubOutR subinstr "tootjr", ipitch
	if (gi03on==1) then  
		AssignSend		        p1, 0.25, 0.1, gi03amp
		SendOut			        p1, aSubOutL, aSubOutR
	endif
endin ; end ins 3
instr 4
	ipitch = p4
	ivel 	= p5
	aSubOutL, aSubOutR subinstr "tootjr", ipitch
	if (gi04on==1) then  
		AssignSend		        p1, 0.25, 0.2, gi04amp
		SendOut			        p1, aSubOutL, aSubOutR
	endif
endin ; end ins 4
instr 5
	ipitch = p4
	ivel 	= p5
	aSubOutL, aSubOutR subinstr "tootjr", ipitch
	if (gi05on==1) then  
		AssignSend		        p1, 0.25, 0.2, gi05amp
		SendOut			        p1, aSubOutL, aSubOutR
	endif
endin ; end ins 5

</CsInstruments>
<CsScore>
t 0 60 ; tempo 

; EFFECTS MATRIX
; Chorus to Reverb (210)
i100 0 0 200 210 0.0
; Chorus to Output (220)
i100 0 0 200 220 0.2
; Reverb (210) to Output (220)
i100 0 0 210 220 0.05

; 200:1 MASTER EFFECT CONTROLS
; Chorus.
; Insno Start   Dur Delay   Divisor of Delay
i200   0       -1      20      10
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 210:1 Reverb.
; Insno Start   Dur Delay   Pitch mod   Cutoff
i210   0       -1      0.75    0.01       12000
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 220:1 Master output. 
i220   0       -1  
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;    

; 1:1
; Include score for i1
#include "sco/Channel1.sco"
; 2:1
; Include score for i2
#include "sco/Channel2.sco"
; 3:1
; Include score for i3
#include "sco/Channel3.sco"
; 4:1
; Include score for i4
#include "sco/Channel4.sco"
; 5:1
; Include score for i5
#include "sco/Channel5.sco"

</CsScore>
</CsoundSynthesizer>
<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>100</x>
 <y>100</y>
 <width>320</width>
 <height>240</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="nobackground">
  <r>255</r>
  <g>255</g>
  <b>255</b>
 </bgcolor>
</bsbPanel>
<bsbPresets>
</bsbPresets>
