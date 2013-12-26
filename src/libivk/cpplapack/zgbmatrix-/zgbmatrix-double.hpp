//=============================================================================
/*! zgbmatrix*=double operator */
inline zgbmatrix& zgbmatrix::operator*=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgbmatrix::operator*=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_((KL+KU+1)*N, d, Array, 1);
  return *this;
}

//=============================================================================
/*! zgbmatrix/=double operator */
inline zgbmatrix& zgbmatrix::operator/=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgbmatrix::operator/=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_((KL+KU+1)*N, 1./d, Array, 1);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! zgbmatrix*double operator */
inline _zgbmatrix operator*(const zgbmatrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const zgbmatrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgbmatrix newmat(mat.M, mat.N, mat.KL, mat.KU);
  for(long i=0; i<(newmat.kl+newmat.ku+1)*newmat.n; i++){
    newmat.array[i] =mat.Array[i]*d;
  }
  
  return _(newmat);
}

//=============================================================================
/*! zgbmatrix/double operator */
inline _zgbmatrix operator/(const zgbmatrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const zgbmatrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  double inv_d(1./d);
  
  zgbmatrix newmat(mat.M, mat.N, mat.KL, mat.KU);
  for(long i=0; i<(newmat.kl+newmat.ku+1)*newmat.n; i++){
    newmat.array[i] =d*mat.Array[i]*inv_d;
  }
  
  return _(newmat);
}
