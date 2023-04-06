// Author: Marc Comino 2018

#include <main_window.h>

#include <QFileDialog>
#include <QMessageBox>

#include "./ui_main_window.h"

namespace gui {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::show() { QMainWindow::show(); }

void MainWindow::on_actionQuit_triggered() { close(); }

void MainWindow::on_actionLoad_triggered() {
  QString filename = QFileDialog::getExistingDirectory(
      this, "Choose a directory.", ".", QFileDialog::Option::ShowDirsOnly);
  if (!filename.isNull()) {
    if (!ui_->glwidget->LoadVolume(filename))
      QMessageBox::warning(this, tr("Error"),
                           tr("The selected volume could not be opened."));
  }
}

// Implementation of the functions (all of them are very similar)
void MainWindow::on_redmin_slider_valueChanged(int rmin) {
    // Modify the text near the slider accordingly for the user to see what is the current value
    ui_->redmin_label->setText(QString::number((double) rmin / 100, 'f', 2)); // Always print 2 decimal places
    // Update the value on the glwidget class
    ui_->glwidget->update_redmin((float) rmin / 100);
}

void MainWindow::on_redmax_slider_valueChanged(int rmax) {
    ui_->redmax_label->setText(QString::number((double) rmax / 100, 'f', 2));
    ui_->glwidget->update_redmax((float) rmax / 100);
}

void MainWindow::on_greenmin_slider_valueChanged(int gmin) {
    ui_->greenmin_label->setText(QString::number((double) gmin / 100, 'f', 2));
    ui_->glwidget->update_greenmin((float) gmin / 100);
}

void MainWindow::on_greenmax_slider_valueChanged(int gmax) {
    ui_->greenmax_label->setText(QString::number((double) gmax / 100, 'f', 2));
    ui_->glwidget->update_greenmax((float) gmax / 100);
}

void MainWindow::on_bluemin_slider_valueChanged(int bmin) {
    ui_->bluemin_label->setText(QString::number((double) bmin / 100, 'f', 2));
    ui_->glwidget->update_bluemin((float) bmin / 100);
}

void MainWindow::on_bluemax_slider_valueChanged(int bmax) {
    ui_->bluemax_label->setText(QString::number((double) bmax / 100, 'f', 2));
    ui_->glwidget->update_bluemax((float) bmax / 100);
}

void MainWindow::on_dialx_valueChanged(int x) {
    ui_->x_label->setText(QString::number((double) x / 5, 'f', 1));
    ui_->glwidget->update_lightposx((float) x / 5);
}

void MainWindow::on_dialy_valueChanged(int y) {
    ui_->y_label->setText(QString::number((double) y / 5, 'f', 1));
    ui_->glwidget->update_lightposy((float) y / 5);
}

void MainWindow::on_dialz_valueChanged(int z) {
    ui_->z_label->setText(QString::number((double) z / 5, 'f', 1));
    ui_->glwidget->update_lightposz((float) z / 5);
}

}  //  namespace gui
