//=============================================================================
/*! dgbmatrix*=double operator */
inline dgbmatrix& dgbmatrix::operator*=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::operator*=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_((KL+KU+1)*N, d, Array, 1);
  return *this;
}

//=============================================================================
/*! dgbmatrix/=double operator */
inline dgbmatrix& dgbmatrix::operator/=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::operator/=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_((KL+KU+1)*N, 1./d, Array, 1);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! dgbmatrix*double operator */
inline _dgbmatrix operator*(const dgbmatrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const dgbmatrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dgbmatrix newmat(mat.M, mat.N, mat.KL, mat.KU);
  for(long i=0; i<(newmat.KL+newmat.KU+1)*newmat.N; i++){
    newmat.Array[i] =mat.Array[i]*d;
  }
  
  return _(newmat);
}

//=============================================================================
/*! dgbmatrix/double operator */
inline _dgbmatrix operator/(const dgbmatrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const dgbmatrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  double inv_d(1./d);
  
  dgbmatrix newmat(mat.M, mat.N, mat.KL, mat.KU);
  for(long i=0; i<(newmat.KL+newmat.KU+1)*newmat.N; i++){
    newmat.Array[i] =mat.Array[i]*inv_d;
  }
  
  return _(newmat);
}
