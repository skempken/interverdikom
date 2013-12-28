//=============================================================================
/*!  destroy all the vector data */
inline void _zcovector::destroy() const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zcovector::destroy() const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zcovector::destroy() "
            << " An array at " << Array
            << " is going to be destroyed." << std::endl;
#endif//CPPL_DEBUG
  
  delete [] Array;
}
