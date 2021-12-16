// The MIT License( MIT )
//
// Copyright( c ) 2020 Scott Aron Bloom
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files( the "Software" ), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sub-license, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <QApplication>
#include <QLineEdit>
#include <QCompleter>
#include <QFileSystemModel>

class CCompleterFileSystemModel : public QFileSystemModel
{
public:
    CCompleterFileSystemModel(QObject * parent = 0) :
        QFileSystemModel(parent)
    {
    }

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override
    {
        if (!index.isValid() || index.model() != this)
            return QVariant();

        if (role == Qt::DisplayRole && index.column() == 0)
        {
            QString path = filePath(index);
            if (path.endsWith("\\") || path.endsWith("/"))
                path.chop(1);
            return path;
        }
        return QFileSystemModel::data(index, role);
    }
};

int main( int argc, char ** argv )
{
    QApplication appl( argc, argv );

    auto fsm = new CCompleterFileSystemModel(&appl);
    fsm->setRootPath("/");

    auto completer = new QCompleter(&appl);
    completer->setModel(fsm);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setCaseSensitivity(Qt::CaseInsensitive);


    QLineEdit le;
    le.setCompleter(completer);
    le.show();
    return appl.exec();
}
