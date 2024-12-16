; Hello Message !!
; Dealing With INTs
MOV RAX,0x100
INT 0x23,0x01
INT 0x21,0x09

; Dealing With Memory

MOV ECX,20
MOV [0x100],RCX
MOV RBX,[0x100]
MOV [0x200],15      ; Moving Immidiate To Memory Dirictly Witout Any Registers 
ADD RCX,RBX
DIV [0X100],2
MUL EBX,[0X100]
ADD [0X100],30
INC [0X100]

; Some Instructions "With Our New Custom Instructions

MOV EAX,17
MOV ECX,20
MOV RBX,RAX
ADD RCX,RBX
POW RBX,2
MOV ECX,3
MOV EBX,27
ROOT RAX,RBX,RCX
AVG RAX,RBX,RCX
MOD RAX,RCX
ISPRIME RSI,RCX
ISPRIME RAX,RBX
MIN RAX,RCX,RBX
MAX RAX,RCX,RBX

; Dealing With CMPs And  UnConditional Jumps And Conditional Jumps

CMP EAX, 17
JE Label03
JNE Label04

; Laabel 0
Label00:
    MOV EAX, 200
    JMP Label04
    
; Label 1
Label01:
    MOV EAX, 100
    JMP Label04
    
; Laabel 2
Label02:
    MOV ECX, 300
    JMP Final

; Laabel 3    
Label03:
    MOV ECX, 400
    JMP Final

; Laabel 4
Label04:
    ; Continue with the rest of the code
    CMP ECX, 3
    JE Label02
    JL Label04

; Final Label    
Final:
    ; Final Instructions
    MOV EBX, 500
    ; Goodbye Message 
    MOV RAX,0x100
    MOV [0x100],"GoodBye!!"
    INT 0x21,0x09
