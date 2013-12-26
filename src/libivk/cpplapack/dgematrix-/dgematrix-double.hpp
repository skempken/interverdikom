//=============================================================================
/*! dgematrix*=double operator */
inline dgematrix& dgematrix::operator*=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::operator*=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(M*N, d, Array, 1);
  return *this;
}

//=============================================================================
/*! dgematrix/=double operator */
inline dgematrix& dgematrix::operator/=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::operator/=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(M*N, 1./d, Array, 1);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! dgematrix*double operator */
inline _dgematrix operator*(const dgematrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const dgematrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dgematrix newmat(mat.M, mat.N);
  for(long i=0; i<mat.M*mat.N; i++){ newmat.Array[i] =mat.Array[i]*d; }
  
  return _(newmat);
}

//=============================================================================
/*! dgematrix/double operator */
inline _dgematrix operator/(const dgematrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const dgematrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  double inv_d(1./d);
  
  dgematrix newmat(mat.M, mat.N);
  for(long i=0; i<mat.M*mat.N; i++){ newmat.Array[i] =mat.Array[i]*inv_d; }
  
  return _(newmat);
}
