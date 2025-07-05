#pragma once

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class handles the main GUI operations
 * for vehicle rental, customer registration, and rental history.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addVehicleButton_clicked();
    void on_rentButton_clicked();
    void on_returnButton_clicked();
    void on_refreshButton_clicked();
    void on_addCustomerButton_clicked();
    void on_deleteVehicleButton_clicked();
    void on_generateReportButton_clicked();  // ✅ This is the new slot for CSV export

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    void setupDatabase();
    void refreshView();
};
