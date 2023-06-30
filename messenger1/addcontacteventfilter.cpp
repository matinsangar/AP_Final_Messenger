#include "addcontacteventfilter.h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QUiLoader>
#include <QFile>
#include <QFileInfo>
bool AddContactEventFilter::eventFilter(QObject* obj, QEvent* event){
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton)
        {
            qDebug() << "Widget clicked!";
            // Perform your action here when the widget is clicked

            //loading addcontact.ui
            QUiLoader loader;
            QString filePath = QString::fromLocal8Bit(__FILE__);    //__FILE__ is a macro
            QFileInfo fileInfo(filePath);
            QString sourceDirectory = fileInfo.absolutePath() + "/addcontact.ui";

            QFile file(sourceDirectory);
            try{
                file.open(QFile::ReadOnly);
                if(!file.isOpen())
                    throw(file.errorString());

                myWidget = loader.load(&file);
                myWidget->setWindowTitle("Add");
                myWidget->show();
                myWidget->setFixedSize(myWidget->width(),myWidget->height());
                file.close();

                QPushButton* addButton = myWidget->findChild<QPushButton*>("addButton",Qt::FindChildOption::FindChildrenRecursively);
                connect(addButton,&QPushButton::clicked,this,&AddContactEventFilter::on_addButton_clicked);
            }catch(QString error){
                qDebug() << error;
            }

            //setting icon for widget
            try{
                QString iconPath = QString::fromLocal8Bit(__FILE__);
                QFileInfo iconInfo(iconPath);
                QString iconDirectory = iconInfo.absolutePath() + "/ICons/avatar.ico";
                QFile temp(iconDirectory);
                if(!temp.exists())
                    throw("Icon Not Found.");
                QIcon *icon = new QIcon(iconDirectory);
                myWidget->setWindowIcon(*icon);
            } catch(char const* error){
                qDebug() << error;
            }
            // You can also access the widget using obj, if needed
            // For example:
            // QWidget* widget = qobject_cast<QWidget*>(obj);
        }
    }

    return QObject::eventFilter(obj, event);
}

void AddContactEventFilter::on_addButton_clicked(){
    //get the name here and manipulate it
    QLineEdit* nameLineEdit = myWidget->findChild<QLineEdit*>("nameLineEdit",Qt::FindChildOption::FindChildrenRecursively);
    qDebug() << nameLineEdit->text();

    nameLineEdit->setText("");
    myWidget->close();
}
