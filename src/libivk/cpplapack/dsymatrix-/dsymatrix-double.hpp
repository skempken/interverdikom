//=============================================================================
/*! dsymatrix*=double operator */
inline dsymatrix& dsymatrix::operator*=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::operator*=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(N*N, d, Array, 1);
  return *this;
}

//=============================================================================
/*! dsymatrix/=double operator */
inline dsymatrix& dsymatrix::operator/=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::operator/=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(N*N, 1./d, Array, 1);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! dsymatrix*double operator */
inline _dsymatrix operator*(const dsymatrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const dsymatrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dsymatrix newmat(mat.N);
  for(long i=0; i<mat.N*mat.N; i++){ newmat.Array[i] =mat.Array[i]*d; }
  
  return _(newmat);
}

//=============================================================================
/*! dsymatrix/double operator */
inline _dsymatrix operator/(const dsymatrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const dsymatrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  double inv_d(1./d);
  
  dsymatrix newmat(mat.N);
  for(long i=0; i<mat.N*mat.N; i++){ newmat.Array[i] =mat.Array[i]*inv_d; }
  
  return _(newmat);
}
