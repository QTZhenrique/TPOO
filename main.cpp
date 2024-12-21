#include "Buffer/Buffer.h"
#include "Simulador/Simulador.h"
#include "UI/UI.h"

int main(){
    Simulador s;
    UI ui(s);
    ui.executa();
    return 0;
}