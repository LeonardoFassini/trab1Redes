#define leftson(x) (2 * x) //Filho a esquerda
#define rightson(x) (2 * x + 1) //Filho a direita
#define dad(x) (x % 2 ? (x-1)/2 : x/2) //Pai (Se for par ou ímpar)
#define valido(x, last) (x <= last)

int insert(int dist, int p, int last, int heap[][2]);
int extract(int heap[][2], int last);
void checaHeapFilho(int i, int heap[][2], int last);
int checaHeapPai(int i, int heap[][2]);
