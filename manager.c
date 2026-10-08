#include <stdio.h>

typedef struct {
    char nombre[30];
    int popularidad;
    int energia;
    int energia_max;
    int fans;
} Idol;

void mostrar(const Idol *idol) {
    if (idol == NULL) return;

    printf("Nombre: %s\n", idol->nombre);
    printf("Popularida: %d\n", idol->popularidad);
    printf("Energia: %d/%d\n", idol->energia, idol->energia_max);
    printf("Fans: %d\n", idol->fans);
}

int limitar(int valor, int minimo, int maximo) {
    if (valor < minimo) return minimo;
    if (valor > maximo) return maximo;
    return valor;
}

void ensayar(Idol *i) {
    if (i == NULL) return;

    i->popularidad += 5;
    i->energia = limitar(i->energia - 20, 0, i->energia_max);
}

void descansar(Idol *i) {
    if (i == NULL) return;

    i->energia = limitar(i->energia + 20, 0, i->energia_max);
}

int main() {
    Idol jennie = {"jennie", 50, 100, 100, 12000};
    Idol *p = &jennie;

    printf("%p\n", (void *)p);
    printf("%p\n", (void *)&jennie);

    mostrar(&jennie);

    printf("\n=== Ensayos ===\n");
    for (int k = 1; k <= 5; k++) {
        ensayar(&jennie);
        printf("Ensayo %d -> ", k);
        mostrar(&jennie);
    }

    printf("\n=== Descansos ===\n");
    for (int k = 1; k <= 5; k++) {
        descansar(&jennie);
        printf("Descanso %d -> ", k);
        mostrar(&jennie);
    }

    return 0;
}
