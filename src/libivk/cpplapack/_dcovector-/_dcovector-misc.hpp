//=============================================================================
/*!  destroy all the vector data */
inline void _dcovector::destroy() const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dcovector::destroy() const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dcovector::destroy() "
            << " An array at " << Array
            << " is going to be destroyed." << std::endl;
#endif//CPPL_DEBUG
  
  delete [] Array;
}
