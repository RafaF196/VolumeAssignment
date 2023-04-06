// Author: Marc Comino 2019

#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace gui {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  virtual void show();

 private slots:
  /**
   * @brief on_actionQuit_triggered Closes the application.
   */
  void on_actionQuit_triggered();

  /**
   * @brief on_actionLoad_triggered Opens a file dialog to load a PLY mesh.
   */
  void on_actionLoad_triggered();

  // Obtains the value for each of the sliders when their value is modified
  void on_redmin_slider_valueChanged(int rmin);
  void on_redmax_slider_valueChanged(int rmax);
  void on_greenmin_slider_valueChanged(int gmin);
  void on_greenmax_slider_valueChanged(int gmax);
  void on_bluemin_slider_valueChanged(int bmin);
  void on_bluemax_slider_valueChanged(int bmax);

  // Obtains the value for each of the dial when their value is modified
  void on_dialx_valueChanged(int x);
  void on_dialy_valueChanged(int y);
  void on_dialz_valueChanged(int z);

 private:
  Ui::MainWindow *ui_;
};

}  //  namespace gui

#endif  //  MAIN_WINDOW_H_
