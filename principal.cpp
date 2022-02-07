#include "principal.h"
#include "ui_principal.h"

#define DEFAULT_ANCHO 3

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    // Instanciando la imagen (creando)
    mImagen = new QImage(this->size(),QImage::Format_ARGB32_Premultiplied);
    // Rellenar la imagen de color blanco
    mImagen->fill(Qt::white);
    // Instanciar el Painter a partir de la imagen
    mPainter = new QPainter(mImagen);
    mPainter->setRenderHint(QPainter::Antialiasing);
    // Inicializar otras variables
    mPuedeDibujar = false;
    mColor = Qt::black;
    mAncho = DEFAULT_ANCHO;
    mNumLineas = 0;
    mTipo = 0;
}

Principal::~Principal()
{
    delete ui;
    delete mPainter;
    delete mImagen;
}

void Principal::linea()
{
    mPainter->drawLine(mInicial, mFinal);
    // Mostrar el número de líneas en la barra de estado
    ui->statusbar->showMessage("Número de líneas: " + QString::number(++mNumLineas));
    // Actualizar la interfaz
    update();
}

void Principal::paintEvent(QPaintEvent *event)
{
    // Crear el painter de la ventana principal
    QPainter painter(this);
    // Dibujar la imagen
    painter.drawImage(0, 0, *mImagen);
    // Acepatr el evento
    event->accept();
}

void Principal::mousePressEvent(QMouseEvent *event)
{
    mPuedeDibujar = true;
    mInicial = event->pos();
    event->accept();
}

void Principal::mouseMoveEvent(QMouseEvent *event)
{
    // Validar si se puede dibujar
    if ( !mPuedeDibujar ) {
        event->accept();
        return;
    }
    // Capturar el punto donde se suelta el mouse
    mFinal = event->pos();
    // Crear un pincel y establecer atributos
    QPen pincel;
    pincel.setColor(mColor);
    pincel.setWidth(mAncho);
    mPainter->setPen(pincel);
    if(mTipo==1&&ui->actionLibre->isChecked()){
        linea();
        mInicial = mFinal;
    }
    // Dibujar una linea
    mPainter->setPen(pincel);
    mPainter->drawLine(mInicial, mFinal);
    // Mostrar el número de líneas en la barra de estado
    ui->statusbar->showMessage("Número de líneas: " + QString::number(++mNumLineas));
    // Actualizar la interfaz
    update();
    // actualizar el punto inicial
    mInicial = mFinal;
}

void Principal::mouseReleaseEvent(QMouseEvent *event)
{
    if(mTipo==1 && ui->actionLineas->isChecked()){
        mPainter->drawLine(mInicial, mFinal);
    }else if(mTipo==2 && ui->actionRect_nculos->isChecked()){
        mPainter->drawRect(mInicial.x(),mInicial.y(),mFinal.x()-mInicial.x(),mFinal.y()-mInicial.y());
    }else if(mTipo==3 && ui->actionCircunferencias->isChecked()){
        mPainter->drawEllipse(mInicial.x(),mInicial.y(),mFinal.x()-mInicial.x(),mFinal.y()-mInicial.y());
    }
    mPuedeDibujar = false;
    // Aceptar el vento
    event->accept();
    update();
}

void Principal::on_actionAncho_triggered()
{
    mAncho = QInputDialog::getInt(this,
                                  "Ancho del pincel",
                                  "Ingrese el ancho del pincel de dibujo",
                                  mAncho,
                                  1, 100);
}

void Principal::on_actionSalir_triggered()
{
    this->close();
}

void Principal::on_actionColor_triggered()
{
    mColor = QColorDialog::getColor(mColor,
                                    this,
                                    "Color del pincel");
}

void Principal::on_actionNuevo_triggered()
{
    mImagen->fill(Qt::white);
    mNumLineas = 0;
    update();
}

void Principal::on_actionGuardar_triggered()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar imagen",
                                                         QString(),
                                                         "Imágenes (*.png)");
    if ( !nombreArchivo.isEmpty() ){
        if (mImagen->save(nombreArchivo))
            QMessageBox::information(this,
                                     "Guardar imagen",
                                     "Archivo almacenado en: " + nombreArchivo);
        else
            QMessageBox::warning(this,
                                 "Guardar imagen",
                                 "No se pudo almacenar la imagen.");
    }
}

void Principal::on_actionRect_nculos_triggered()
{
    mTipo=2;
    ui->actionRect_nculos->setCheckable(true);
    ui->actionLibre->setChecked(false);
    ui->actionLineas->setCheckable(false);
    ui->actionCircunferencias->setCheckable(false);
}

void Principal::on_actionCircunferencias_triggered()
{
    mTipo=3;
    ui->actionLibre->setChecked(false);
    ui->actionLineas->setCheckable(false);
    ui->actionRect_nculos->setCheckable(false);
    ui->actionCircunferencias->setCheckable(true);
}

void Principal::on_actionLineas_triggered()
{
    mTipo=1;
    ui->actionLibre->setChecked(false);
    ui->actionLineas->setCheckable(true);
    ui->actionRect_nculos->setCheckable(false);
    ui->actionCircunferencias->setCheckable(false);
}

void Principal::on_actionAcerca_del_creador_triggered()
{
    // crear un objeto de la ventana "AcercaTienda"
    Acerca *dialogo=new Acerca(this);
    //mostar ventana
    dialogo->exec();
}
