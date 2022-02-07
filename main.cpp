#include "principal.h"

#include <QInputDialog>
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator traduccion;
    QStringList idioma;
    idioma << "Castellano" << "Japones";
    QString idiomaSeleccionado = QInputDialog::getItem(NULL,"Idioma", "Seleccione un idioma",idioma);
    if (idiomaSeleccionado == "Japones"){
        traduccion.load("tienda_jp_JP.qm");
    }else if (idiomaSeleccionado != "Castellano"){
        a.installTranslator(&traduccion);
    }
    Principal w;
    w.show();
    return a.exec();
}
