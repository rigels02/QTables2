#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QInputDialog>


#include "model/mtable.h"

namespace Ui {
class UpdateDialog;
}

class UpdateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateDialog(QWidget *parent = 0,QList<TableData> *data = 0);
    ~UpdateDialog();
    TableData fromForm() const;
    void toForm(int selIdx);
    void addForm();

private slots:
    void on_btnUpdate_clicked();


    void on_btnCat_clicked();

    void on_btnNote_clicked();

private:
    Ui::UpdateDialog *ui;
    QList<TableData> *m_data;

private:
    QStringList categoryList() const;
    QStringList noteList() const;
private:
    bool isValid(QString &info) const;
};

#endif // UPDATEDIALOG_H
