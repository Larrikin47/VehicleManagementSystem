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
    /**
     * @brief Constructor - initializes the GUI and database connection.
     * @param parent Optional parent widget (default: nullptr).
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor - closes the database connection and cleans up.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Triggered when the "Add Vehicle" button is clicked.
     * Opens a dialog to input vehicle details and adds to the database.
     */
    void on_addVehicleButton_clicked();

    /**
     * @brief Triggered when the "Rent" button is clicked.
     * Opens a dialog to assign a vehicle to a customer.
     */
    void on_rentButton_clicked();

    /**
     * @brief Triggered when the "Return" button is clicked.
     * Sets the selected vehicle’s status to "Available".
     */
    void on_returnButton_clicked();

    /**
     * @brief Triggered when the "Refresh" button is clicked.
     * Updates the vehicle and rental table views.
     */
    void on_refreshButton_clicked();

    /**
     * @brief Triggered when the "Add Customer" button is clicked.
     * Opens a dialog to input customer information and adds to the database.
     */
    void on_addCustomerButton_clicked();

private:
    Ui::MainWindow *ui;   ///< Pointer to the UI layout
    QSqlDatabase db;      ///< SQLite database connection

    /**
     * @brief Initializes and creates the database tables if needed.
     */
    void setupDatabase();

    /**
     * @brief Updates the vehicle and rental views in the UI.
     */
    void refreshView();
};
