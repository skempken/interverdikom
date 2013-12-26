//=============================================================================
/*! zhematrix*=double operator */
inline zhematrix& zhematrix::operator*=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::operator*=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(N*N, d, Array, 1);
  return *this;
}

//=============================================================================
/*! zhematrix/=double operator */
inline zhematrix& zhematrix::operator/=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::operator/=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(N*N, 1./d, Array, 1);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! zhematrix*double operator */
inline _zhematrix operator*(const zhematrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const zhematrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zhematrix newmat(mat.N);
  for(long i=0; i<mat.N*mat.N; i++){ newmat.array[i] =mat.Array[i]*d; }
  
  return _(newmat);
}

//=============================================================================
/*! zhematrix/double operator */
inline _zhematrix operator/(const zhematrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const zhematrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  double inv_d(1./d);
  
  zhematrix newmat(mat.N);
  for(long i=0; i<mat.N*mat.N; i++){ newmat.array[i] =mat.Array[i]*inv_d; }
  
  return _(newmat);
}
