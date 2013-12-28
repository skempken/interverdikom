//=============================================================================
//! (DO NOT USE) Shaddow Complex-double Class for zhematrix
class __zhecomplex : public std::complex<double>
{
private:
  //// objects ////
  std::complex<double>& value;
  int i, j;
  
public:
  //// constructer ////
  inline __zhecomplex(std::complex<double>& _value, const int& _i, const int& _j)
    : std::complex<double>( _i < _j ? std::conj( _value ) : _value ), 
      value( _value ) 
  {
#ifdef  CPPL_VERBOSE
    std::cerr << "# [MARK] __zhecomplex(const std::complex<double>&, const int&, const int&)"
              << std::endl;
#endif//CPPL_VERBOSE
    
    i = _i;
    j = _j;
  }
  
  //// operator= ////
  inline __zhecomplex& operator=(const std::complex<double>& _value)
  {
#ifdef  CPPL_VERBOSE
    std::cerr << "# [MARK] operator=(const std::complex<double>&)"
              << std::endl;
#endif//CPPL_VERBOSE
    
#ifdef  CPPL_DEBUG
    if( i==j && std::fabs(_value.imag()) > CPPL_EPS ){
      std::cerr << "[WARNING] __zhecomplex::operator="
                << "(const std::complex<double>&)" << std::endl
                << "Diagonal components of a hermitian matrix "
                << "have to be real numbers." << std::endl
                << "Your input to the (" << i << "," << j << ") element "
                << "was a complex number, " << _value << "." << std::endl;
    }
#endif//CPPL_DEBUG
    
    std::complex<double>::operator=( _value );
    value = ( i < j ? std::conj( _value ) : _value );
    return *this;
  }  
};
