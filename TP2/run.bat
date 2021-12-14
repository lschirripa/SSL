flex lex.l

bison -d sin.y

gcc lex.yy.c sin.tab.c -o comp -lfl

start comp.exe