###!----------------------------------------------
###!
###! JOC DE PROVES DE LA CLASSE WORD_TOOLKIT
###!
###!----------------------------------------------
###!
###!  1. es_canonic
###!  2. anagrama_canonic
###!  3. mes_frequent
###!
###!------------------------------------------------------------------
###1 es_canonic
###!------------------------------------------------------------------
###!
#es_canonic ""
true
##true
#es_canonic A
true
##true
#es_canonic AA
true
##true
#es_canonic AAA
true
##true
#es_canonic ABCED
false
##false
#es_canonic ABCDEFGHIJKLMNOPQRSTUVWXYZ
true
##true
###!
###!------------------------------------------------------------------
###2 anagrama_canonic
###!------------------------------------------------------------------
###!
#canonic ""

##
#canonic A
A
##A
#canonic AA
AA
##AA
#canonic AAA
AAA
##AAA
#canonic ABCED
ABCDE
##ABCDE
#canonic ABCDEFGHIJKLMNOPQRSTUVWXYZ
ABCDEFGHIJKLMNOPQRSTUVWXYZ
##ABCDEFGHIJKLMNOPQRSTUVWXYZ
#canonic BDFHJLNPRTVXZACEGIKMOQSUWY
ABCDEFGHIJKLMNOPQRSTUVWXYZ
##ABCDEFGHIJKLMNOPQRSTUVWXYZ
###!
###!------------------------------------------------------------------
###3 mes_frequent
###!------------------------------------------------------------------
###!
#mes_frequent "" [A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z]
A
##A
#mes_frequent ABCDEFGHIJKLMNOPQRSTUVWXYZ [A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z]

##
#mes_frequent ABCDEFGHIKLMNOPQRTUVWXYZ [A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z]
J
##J
#mes_frequent ABCDEFGHIKLMNOPQRTUVWXYZ [A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,S]
S
##S
#mes_frequent "" [HOLA,ADEU]
A
##A
#mes_frequent A [HOLA,ADEU]
D
##D
#mes_frequent ADEHLOU [HOLA,ADEU]

##
#mes_frequent "" [JOCS,DE,PROVES,DE,LA,CLASSE,WORD,TOOLKIT]
O
##O
#mes_frequent O [JOCS,DE,PROVES,DE,LA,CLASSE,WORD,TOOLKIT]
E
##E
#mes_frequent OE [JOCS,DE,PROVES,DE,LA,CLASSE,WORD,TOOLKIT]
S
##S
#mes_frequent OES [JOCS,DE,PROVES,DE,LA,CLASSE,WORD,TOOLKIT]
D
##D
#mes_frequent OESD [JOCS,DE,PROVES,DE,LA,CLASSE,WORD,TOOLKIT]
L
##L
#mes_frequent OESDL [JOCS,DE,PROVES,DE,LA,CLASSE,WORD,TOOLKIT]
A
##A
#mes_frequent OESDLA [JOCS,DE,PROVES,DE,LA,CLASSE,WORD,TOOLKIT]
C
##C
#mes_frequent OESDLAC [JOCS,DE,PROVES,DE,LA,CLASSE,WORD,TOOLKIT]
R
##R
#mes_frequent OESDLACR [JOCS,DE,PROVES,DE,LA,CLASSE,WORD,TOOLKIT]
T
##T
#mes_frequent OESDLACRT [JOCS,DE,PROVES,DE,LA,CLASSE,WORD,TOOLKIT]
I
##I
#mes_frequent OESDLACRTI [JOCS,DE,PROVES,DE,LA,CLASSE,WORD,TOOLKIT]
J
##J
#mes_frequent OESDLACRTIJ [JOCS,DE,PROVES,DE,LA,CLASSE,WORD,TOOLKIT]
K
##K
#mes_frequent OESDLACRTIJK [JOCS,DE,PROVES,DE,LA,CLASSE,WORD,TOOLKIT]
P
##P
#mes_frequent OESDLACRTIJKP [JOCS,DE,PROVES,DE,LA,CLASSE,WORD,TOOLKIT]
V
##V
#mes_frequent OESDLACRTIJKPV [JOCS,DE,PROVES,DE,LA,CLASSE,WORD,TOOLKIT]
W
##W
#mes_frequent OESDLACRTIJKPVW [JOCS,DE,PROVES,DE,LA,CLASSE,WORD,TOOLKIT]

##
###!
###!
###!
[0/0]
