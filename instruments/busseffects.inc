/* busseffects.inc */

/* Notes */
/* I'm not sure the chorus is working with the variables */
/* as I've set them */


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; M I X E R   L E V E L S
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

instr 100 ; Mixer level
        isend=p4
        ibuss0=p5
        igain0=p6
        MixerSetLevel           isend, ibuss0, igain0
endin

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; B U S S   E F F E C T S 
; Buss relates to how separate audio channels are routed 
; through a mixing desk - in this case a virtual one.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

instr 200               ; Chorus by J. Lato
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; p4 = delay in milliseconds
; p5 = divisor of p4
; Chorus effect from http://www.jlpublishing.com/Csound.htm
; Some of its parameters are accesible through the score.
a1 MixerReceive            200, 0
a2 MixerReceive            200, 1
idlyml=p4      ;delay in milliseconds
k1                      poscil                  idlyml/p5, 1, 2
ar1l vdelay3   a1, idlyml/5+k1, 900    ;delayed sound 1
ar1r                    vdelay3                 a2, idlyml/5+k1, 900    ;delayed sound 1
k2                      poscil                  idlyml/p5, .995, 2
ar2l                    vdelay3                 a1, idlyml/5+k2, 700    ;delayed sound 2
ar2r                    vdelay3                 a2, idlyml/5+k2, 700    ;delayed sound 2
k3                      poscil                  idlyml/p5, 1.05, 2
ar3l                    vdelay3                 a1, idlyml/5+k3, 700    ;delayed sound 3
ar3r                    vdelay3                 a2, idlyml/5+k3, 700    ;delayed sound 3
k4                      poscil                  idlyml/p5, 1, 2
ar4l                    vdelay3                 a1, idlyml/5+k4, 900    ;delayed sound 4
ar4r                    vdelay3                 a2, idlyml/5+k4, 900    ;delayed sound 4
aoutl                   = (a1+ar1l+ar2l+ar3l+ar4l)*.5
aoutr                   = (a2+ar1r+ar2r+ar3r+ar4r)*.5
                        ; To the reverb unit
                        MixerSend               aoutl, 200, 210, 0
                        MixerSend               aoutr, 200, 210, 1
                        ; To the output mixer
                        MixerSend               aoutl, 200, 220, 0
                        MixerSend               aoutr, 200, 220, 1
                        endin

instr 210 ; Reverb by Sean Costello / J. Lato
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
idelay    = p4      
ipitchmod = p5  
icutoff   = p6              
ainL                    MixerReceive            210, 0
ainR                    MixerReceive            210, 1
aoutL, aoutR            reverbsc                ainL, ainR, idelay, icutoff, sr, ipitchmod, 0
                        ; To the master output.
                        MixerSend               aoutL, 210, 220, 0
                        MixerSend               aoutR, 210, 220, 1
                        endin
instr 211 ; Reverb by Sean Costello / J. Lato
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
idelay =                       p4      
ipitchmod =                       p5  
icutoff =                       p6              
ainL                    MixerReceive            210, 0
ainR                    MixerReceive            210, 1
aoutL, aoutR            reverbsc                ainL, ainR, idelay, icutoff, sr, ipitchmod, 0
                        ; To the master output.
                        MixerSend               aoutL, 210, 220, 0
                        MixerSend               aoutR, 210, 220, 1
                        endin                        
                        
instr 220               ; Master output
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; p4 = level
; p5 = fadein + fadeout
; Applies a bass enhancement, compression and fadeout
; to the whole piece, outputs signals, and clears the mixer.
; Receive audio from the master mixer buss.
a1                      MixerReceive            220, 0
a2                      MixerReceive            220, 1
                        ; Enhance the bass.
al1                     butterlp                a1, 100
al2                     butterlp                a2, 100
a1                      =                       al1 * 1.5 + a1
a2                      =                       al2 * 1.5 + a2
                        ; Remove DC bias.
a1blocked               dcblock                 a1
a2blocked               dcblock                 a2
                        ; Apply compression.
a1 compress                a1, a1, 0, 48, 60, 3, .01, .05, .05
a2 compress                a2, a2, 0, 48, 60, 3, .01, .05, .05
                        ; Output audio.
outs                    a1blocked, a2blocked
; Reset the busses for the next kperiod.
MixerClear
endin