#ifndef TABLEPLOTLINK_H_
#define TABLEPLOTLINK_H_

#include <vector>

class IvkTableWidget;

/// Specifies a value range from an IvkTableWidget to export as QwtCurve
class TablePlotLink
{
public:
	/// Type of value to extrace
	/**
	 * - RowIndexes: Use row indexes
	 * - ColumnIndexes: Use column indexes
	 * - RowValues Use values of a specific row
	 * - ColumnValues Use Values of a specific column
	 */
	enum ValueType { RowIndexes, ColumnIndexes, RowValues, ColumnValues };
	
	/// Constructor for using values
	/**
	 * \param valueType rowValues or colValues
	 * \param valueIndex Index of the row or column from which values should be taken
	 */
	TablePlotLink(ValueType valueType, int valueIndex);
	
	/// Constructor for using indexes
	/**
	 * \param valueType rowIndex or colIndex
	 * \param indexFactor Factor by which indexes should be multiplied
	 * \param offset Offset which is added to all indices
	 */
	TablePlotLink(ValueType valueType, double indexFactor = 1.0f, int indexOffset = 0);
	
	/// Destructor
	virtual ~TablePlotLink();
	
	/// Sets the associated table widget
	/**
	 * \param table Pointer to table widget
	 */
	void setTableWidget(IvkTableWidget *table)
		{ this->tablePointer = table; }
	
	/// Return the specified values
	/**
	 * \return Vector of values
	 */
	std::vector<double> getValues();
	
private:
	/// Helper function: Retrieves indices
	std::vector<double> getIndexValues();
	
	/// Helper function: Retrieves row or column values
	std::vector<double> getTableValues();
	
	/// Get maximum number of values which can be returned
	/**
	 * \return Value count
	 */
	unsigned int getMaxValueCount();
	
	/// Gets the Value for a specific index of the result vector
	/**
	 * \index Vector index
	 * \return Requested value
	 */
	double getAppropriateCellValue(unsigned int index);

	/// Sets whether it's possible to extrace values using the specified parameters
	bool isValid;
	
	/// Associated IvkTableWidget object
	class IvkTableWidget *tablePointer;
	
	/// Value type to extract
	ValueType valueType;
	
	/// Factor by which to multiply indices
	double indexFactor;
	
	/// Offset which is added to all index values
	int indexOffset;
	
	/// Row or column index to use for extraction
	unsigned int valueIndex;
};

#endif /*TABLEPLOTLINK_H_*/
