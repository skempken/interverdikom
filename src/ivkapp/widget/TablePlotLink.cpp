#include "TablePlotLink.h"

#include <QMessageBox>

#include "MainWindow.h"
#include "IvkTableWidget.h"

using namespace std;

TablePlotLink::TablePlotLink(ValueType valueType, double indexFactor, int indexOffset) :
	tablePointer(0), valueType(valueType), indexFactor(indexFactor), indexOffset(indexOffset)
{
	if ((valueType == RowValues) || (valueType == ColumnValues))
		isValid = false;
	else
		isValid = true;
}
	
TablePlotLink::TablePlotLink(ValueType valueType, int valueIndex) :
	tablePointer(0), valueType(valueType), valueIndex(static_cast<unsigned int>(valueIndex))
{
	if ((valueType == RowIndexes) || (valueType == ColumnIndexes))
		isValid = false;
	else
		isValid = true;
}

TablePlotLink::~TablePlotLink() {}
	
vector<double> TablePlotLink::getValues()
{
	
	if ((!isValid) || (!tablePointer))
		return vector<double>();
	else if ((valueType == RowIndexes) || (valueType == ColumnIndexes)) 
		return getIndexValues();
	else if ((valueType == RowValues) || (valueType == ColumnValues))
		return getTableValues();
	else
		return vector<double>();
}

vector<double> TablePlotLink::getTableValues()
{
	vector<double> result;
	
	for (unsigned int i = 0; i < getMaxValueCount(); i++)
	{
		result.push_back(getAppropriateCellValue(i));		
	}

	return result;
}

double TablePlotLink::getAppropriateCellValue(unsigned int index)
{
	int i = valueIndex, j = valueIndex;
	
	if (valueType == ColumnValues)
		i = index;
	else if (valueType == RowValues)
		j = index;
	else
		return 0.0f;
		
	return tablePointer->item(i,j)->text().toDouble();	
}

unsigned int TablePlotLink::getMaxValueCount()
{
	if ((valueType == RowIndexes) || (valueType == RowValues))
		return tablePointer->columnCount();
	else if ((valueType == ColumnIndexes) || (valueType == ColumnValues))
		return tablePointer->rowCount();
	else
		return 0;
}

vector<double> TablePlotLink::getIndexValues()
{
	vector<double> result;
	unsigned int maxIndex = getMaxValueCount();
	
	for (unsigned int i = 0; i < maxIndex; i++)
	{
		result.push_back((i * indexFactor) + indexOffset);
	}
	
	return result;
}
