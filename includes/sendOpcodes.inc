/* sendOpcodes.inc */
/* for use with  */

opcode AssignSend, 0, iiii
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  insno,ic,ir,id 	    xin
  inum			        = floor(insno)
  MixerSetLevel	 	    inum, 200, ic
  MixerSetLevel	 	    inum, 210, ir
  MixerSetLevel	 	    inum, 220, id
endop

opcode SendOut, 0, iaa
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  insno, aleft, aright	  xin
  inum                    = floor(insno)
  MixerSend               aleft, inum, 200, 0
  MixerSend               aright, inum, 200, 1
  MixerSend               aleft, inum, 210, 0
  MixerSend               aright, inum, 210, 1
  MixerSend               aleft, inum, 220, 0
  MixerSend               aright, inum, 220, 1
endop

opcode AssignSendNamed, 0, iiii
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  insno,ic,ir,id      xin
  inum              = floor(insno)
  ;print inum
  MixerSetLevel       inum, 200, ic
  MixerSetLevel       inum, 210, ir
  MixerSetLevel       inum, 220, id
endop

opcode SendOutNamed, 0, iaa
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  insno, aleft, aright    xin
  inum                    = floor(insno)
  ;print inum
  MixerSend               aleft, inum, 200, 0
  MixerSend               aright, inum, 200, 1
  MixerSend               aleft, inum, 210, 0
  MixerSend               aright, inum, 210, 1
  MixerSend               aleft, inum, 220, 0
  MixerSend               aright, inum, 220, 1
endop