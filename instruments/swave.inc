/* swave.inc */

ipthree	= 0.25
ipfour 	= p4

idur = ipthree

ifreq = (ipfour > 15 ? ipfour : cpspch(ipfour))
print ifreq

imyrandom 	random 0, 9
irdvd 		= imyrandom / 4
iroll 		= (60 * int(irdvd)) 
ifreq 		= ifreq + iroll
iamp 		= 100/127 ; 
kenv 		linseg 0, 0.25, 1, 0.75, 0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; A D S R
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; http://www.csounds.com/manual/html/adsr.html
; the volume goes to twice the sustVOL in between
; attTIME and decayTIME - see link above
; 				attTIME		decayTIME	sustVOL		relTIME
; kenv adsr 	0.02, 		0.2, 		iamp, 			0.075
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

aout init 0
ksampnum init 0
kcount = 0
iperiod = sr / ifreq
i2pi = 3.14159 * 2
kincrement = 1.008 ; messing with the loop increment makes it sound more artificial and scratchy (def: 1)

loopStart:
	kphase = (ksampnum % iperiod) / iperiod
	knewval = sin(kphase * i2pi)
	vaset knewval, kcount,aout
	ksampnum = ksampnum + 1

;http://www.csounds.com/manual/html/loop_lt.html
loop_lt kcount, kincrement, ksmps, loopStart 

aout = aout*kenv

outs aout, aout