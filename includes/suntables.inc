/* suntables.inc */
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; F U N C T I O N   T A B L E S
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Waveform for the string-pad
giwave  ftgen  1, 0, 65537,    10,     1, .5, .33, 0.25,  .0, 0.1,  .1, 0.1
gisine   ftgen     2, 0, 65537,    10,     1
giwtsin   init       gisine

; for ins moog
gimandpluk ftgen 0,0,8192,1,"../assets/mandpluk.aiff",0,0,0
giimpuls20 ftgen 0,0,256,1,"../assets/impuls20.aiff",0,0,0

; the "marmstk1.wav" audio file for marimba
gimarmstk1 ftgen 0,0,256,1,"../assets/marmstk1.wav",0,0,0

; for ins 8
itmp  ftgen 4, 0, 16384, 7, 0, 2048, 1, 4096, 1, 4096, -1, 4096, -1, 2048, 0
ift     vco2init -4, 10000, 0, 0, 0, 1

; for ins 9
giSigmoRise	ftgen		0, 0, 8193, 19, 0.5, 1, 270, 1			; rising sigmoid 
giSigmoFall	ftgen		0, 0, 8193, 19, 0.5, 1, 90, 1			; falling sigmoid 

giharpsichord 			ftgen 					0,0,  65537,7,-1,1024,1,1024,-1 ; Kelley harpsichord.
gicosine 				ftgen    				0, 0, 65537,    11,     1 ; Cosine wave. 
giexponentialrise       ftgen                   0, 0, 65537,     5,     .001, 513, 1 ; Exponential rise.
githirteen              ftgen                   0, 0, 65537,     9,     1, .3, 0
giln                    ftgen                   0, 0, 65537,   -12,    20.0 ; Unscaled ln(I(x)) from 0 to 20.0.
gibergeman              ftgen                   0, 0, 65537,    10,     .28, 1, .74, .66, .78, .48, .05, .33, 0.12, .08, .01, .54, 0.19, .08, .05, 0.16, .01, 0.11, .3, .02, 0.2 ; Bergeman f1
gicookblank             ftgen                   0, 0, 65537,    10,     0 ; Blank wavetable for some Cook FM opcodes.
gicook3                 ftgen                   0, 0, 65537,    10,     1, .4, 0.2, 0.1, 0.1, .05
gikellyflute            ftgen                   0, 0, 65537,    10,     1, 0.25, 0.1 ; Kelley flute.
gichebychev             ftgen                   0, 0, 65537,    -7,    -1, 150, 0.1, 110, 0, 252, 0
giffitch1               ftgen                   0, 0, 65537,    10,     1
giffitch2               ftgen                   0, 0, 65537,     5,     1, 1024, .01
giffitch3               ftgen                   0, 0, 65537,     5,     1, 1024, .001
                        ; Rotor Tables
gitonewheel1 			ftgen       			0, 0, 65537,    10,     1, .02, .01
gitonewheel2            ftgen                   0, 0, 65537,    10,     1, 0, 0.2, 0, 0.1, 0, .05, 0, .02
                        ; Rotating Speaker Filter Envelopes
gitonewheel3            ftgen                   0, 0, 65537,     7,     0, 110, 0, 18, 1, 18, 0, 110, 0
gitonewheel4            ftgen                   0, 0, 65537,     7,     0, 80, 0.2, 16, 1, 64, 1, 16, 0.2, 80, 0
                        ; Distortion Tables
gitonewheel5            ftgen                   0, 0, 65537,     8,    -.8, 336, -.78,  800, -.7, 5920, .7,  800, .78, 336, .8
gitonewheel6            ftgen                   0, 0, 65537,     8     -.8, 336, -.76, 3000, -.7, 1520, .7, 3000, .76, 336, .8
                        ; Table for Reed Physical Model
gireedtable ftgen    0, 0, 256,       7,     1, 80, 1, 156, -1, 40, -1

/* suntables.inc */
