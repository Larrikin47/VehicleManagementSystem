#pragma once

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class handles the main GUI operations
 * for vehicle and customer management in the rental system.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructor - initializes the GUI and database.
     * @param parent Optional parent widget.
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor - closes the database and cleans up UI.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Slot triggered when the "Add Vehicle" button is clicked.
     */
    void on_addVehicleButton_clicked();

    /**
     * @brief Slot triggered when the "Rent" button is clicked.
     */
    void on_rentButton_clicked();

    /**
     * @brief Slot triggered when the "Return" button is clicked.
     */
    void on_returnButton_clicked();

    /**
     * @brief Slot triggered when the "Refresh" button is clicked.
     */
    void on_refreshButton_clicked();

    /**
     * @brief Slot triggered when the "Add Customer" button is clicked.
     */
    void on_addCustomerButton_clicked();  // maNewly added

private:
    Ui::MainWindow *ui;   ///< Pointer to the UI layout
    QSqlDatabase db;      ///< SQLite database connection

    /**
     * @brief Initializes the database and creates tables.
     */
    void setupDatabase();

    /**
     * @brief Refreshes the vehicle view from the database.
     */
    void refreshView();
};
