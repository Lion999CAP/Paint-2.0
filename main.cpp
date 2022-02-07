#include "principal.h"

#include <QInputDialog>
#include <QApplication>
#include <QMessageBox>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLocale location;
    QString idioma = location.languageToString(location.language());
    // Objeto para manejar las traducciones
    QTranslator traducion;
    if(idioma == "Japanese"){
        traducion.load(":/miPaint_ja_JA.qm");
    }
    if((idioma != "Japanese") && (idioma != "Spanish")){
        QMessageBox::warning(NULL,"Advertencia","El idioma regional requerido no se encuentra");
    }
    if(idioma != QLocale::Spanish){
        a.installTranslator(&traducion);
    }
    /*
    QTranslator traduccion;
    QStringList idioma;
    idioma << "Castellano" << "Japones";
    QString idiomaSeleccionado = QInputDialog::getItem(NULL,"Idioma", "Seleccione un idioma",idioma);
    if (idiomaSeleccionado == "Japones"){
        traduccion.load("tienda_jp_JP.qm");
    }else if (idiomaSeleccionado != "Castellano"){
        a.installTranslator(&traduccion);
    }
    */
    Principal w;
    w.show();
    return a.exec();
}
