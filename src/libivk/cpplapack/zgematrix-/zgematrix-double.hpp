//=============================================================================
/*! zgematrix*=double operator */
inline zgematrix& zgematrix::operator*=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::operator*=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(M*N, d, Array, 1);
  return *this;
}

//=============================================================================
/*! zgematrix/=double operator */
inline zgematrix& zgematrix::operator/=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::operator/=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(M*N, 1./d, Array, 1);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! zgematrix*double operator */
inline _zgematrix operator*(const zgematrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const zgematrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgematrix newmat(mat.M, mat.N);
  for(long i=0; i<mat.M*mat.N; i++){ newmat.array[i] =mat.Array[i]*d; }
  
  return _(newmat);
}

//=============================================================================
/*! zgematrix/double operator */
inline _zgematrix operator/(const zgematrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const zgematrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  double inv_d(1./d);
  
  zgematrix newmat(mat.M, mat.N);
  for(long i=0; i<mat.M*mat.N; i++){ newmat.array[i] =mat.Array[i]*inv_d; }
  
  return _(newmat);
}
