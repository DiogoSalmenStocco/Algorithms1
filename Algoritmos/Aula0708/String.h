#ifndef STRING_ADT //se esse arquivo já foi definido ele não é definido de novo
#define STRING_ADT

//Estrutura de dados da String: a string em c e o tamanho em int
typedef struct String {
  char *dado;
  int tam;
}String;

/*
HEADERS ou PROTOTIPOS
*/


String* createString(const char *s);
void delString(String *);

char * c_str(String *);

#endif