#include "NavigationPath.h"

#include <iostream>

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QLabel>
#include <QHBoxLayout>

NavigationPath::NavigationPath(QWidget *parent) :
	QWidget(parent), layout((new QHBoxLayout()))
{
	layout->setMargin(0);
	layout->setSpacing(0);
	setLayout(layout);
	layout->addStretch(1);
}

NavigationPath::~NavigationPath()
{
}

void NavigationPath::moduleSelected(class QTreeWidgetItem *item)
{
	setUpdatesEnabled(false);
	QTreeWidgetItem *currentItem = item;
	clearLabels();

	int level = 0;
	bool dotsAdded = false;
	do
	{
		if ((level <= 1) || !currentItem->parent())
		{
			addNavigationLabel(currentItem);

			if (currentItem->parent())
			{
				addSeparator();
			}
		}
		else
		{
			if (!dotsAdded)
			{
				addNavigationLabel("...");
				dotsAdded = true;
				addSeparator();
			}
		}

		currentItem = currentItem->parent();
		level++;
	} while (currentItem != 0);

	setUpdatesEnabled(true);
}

void NavigationPath::clearLabels()
{
	vector<NavPair>::iterator it;

	for (it = navigation.begin(); it != navigation.end(); it++)
	{
		layout->removeWidget((*it).first);
		delete (*it).first;
	}

	navigation.clear();
}

void NavigationPath::setTreeWidget(QTreeWidget *theWidget)
{
	treeWidget = theWidget;
	connect(this,SIGNAL(itemClicked(QTreeWidgetItem*,int)),treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)));
}

void NavigationPath::addNavigationLabel(QTreeWidgetItem *item)
{
	QString text = item->text(0);

	QLabel *newLabel = new QLabel(this);
	newLabel->setText(QString("<a style=\"color:darkgrey\" href=\"%1\">").arg(navigation.size())
			+ text + QString("</a>"));
	newLabel->setCursor(QCursor(Qt::PointingHandCursor));

	connect(newLabel, SIGNAL(linkActivated(QString)), this,
			SLOT(navigationLabelActivated(QString)));

	layout->insertWidget(0, newLabel);
	navigation.push_back(NavPair(newLabel, item));
}

void NavigationPath::addNavigationLabel(QString label)
{
	QLabel *newLabel = new QLabel(this);
	newLabel->setText(QString("<span style=\"color:darkgrey\">") + label
			+ QString("</span>"));
	layout->insertWidget(0, newLabel);
	navigation.push_back(NavPair(newLabel, 0));
}

void NavigationPath::navigationLabelActivated(QString linkText)
{
	QTreeWidgetItem *requestedItem = navigation.at(linkText.toInt()).second;
	treeWidget->setCurrentItem(requestedItem);
	emit itemClicked(requestedItem, 0);
}

void NavigationPath::addSeparator()
{
	QLabel *newLabel = new QLabel(this);
	newLabel->setText("<font color=\"darkgrey\">&nbsp;>&nbsp;</font>");
	layout->insertWidget(0, newLabel);
	navigation.push_back(NavPair(newLabel, 0));
}
