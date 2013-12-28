//=============================================================================
/*! zgematrix*=std::complex<double> operator */
inline zgematrix& zgematrix::operator*=(const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::operator*=(const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_(M*N, d, Array, 1);
  return *this;
}

//=============================================================================
/*! zgematrix/=std::complex<double> operator */
inline zgematrix& zgematrix::operator/=(const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::operator/=(const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_(M*N, 1./d, Array, 1);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! zgematrix*std::complex<double> operator */
inline _zgematrix operator*(const zgematrix& mat, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const zgematrix&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgematrix newmat(mat.M, mat.N);
  for(long i=0; i<mat.M*mat.N; i++){ newmat.array[i] =mat.Array[i]*d; }
  
  return _(newmat);
}

//=============================================================================
/*! zgematrix/std::complex<double> operator */
inline _zgematrix operator/(const zgematrix& mat, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const zgematrix&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::complex<double> inv_d(1./d);
  
  zgematrix newmat(mat.M, mat.N);
  for(long i=0; i<mat.M*mat.N; i++){ newmat.array[i] =mat.Array[i]*inv_d; }
  
  return _(newmat);
}
