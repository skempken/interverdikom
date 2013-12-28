#ifndef MODULELIST_H_
#define MODULELIST_H_

#include <QTreeWidget>
#include <QMimeData>

class ModuleList : public QTreeWidget {
	Q_OBJECT

public:
	class MyMimeData : public QMimeData {
	public:
		MyMimeData(const QList<QTreeWidgetItem *> & indexes) : _indexes(indexes) {setData("application/x-qabstractitemmodeldatalist", QByteArray());}
		const QList<QTreeWidgetItem *> & indexes() const { return _indexes; }
	private:
		QList<QTreeWidgetItem *> _indexes;
	};

	ModuleList(QWidget * parent);

	virtual ~ModuleList();

	void dragMoveEvent(QDragMoveEvent * event);

	void mousePressEvent(QMouseEvent *event);

	void mouseMoveEvent(QMouseEvent *event);

	void dropEvent(QDropEvent * event);

	virtual bool dropMimeData(QTreeWidgetItem *parent, int index, const QMimeData *data, Qt::DropAction action);

	QMimeData *mimeData(const QList<QTreeWidgetItem *> items) const;

	void dragEnterEvent(QDragEnterEvent *e);
};

#endif /* MODULELIST_H_ */
