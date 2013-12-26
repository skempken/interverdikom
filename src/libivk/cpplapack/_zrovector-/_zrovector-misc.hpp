//=============================================================================
/*! destroy all the vector data */
inline void _zrovector::destroy() const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zrovector::destroy() const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zrovector::destroy() const"
            << " An array at " << Array
            << " is going to be destroyed." << std::endl;
#endif//CPPL_DEBUG
  
  delete [] Array;
}
