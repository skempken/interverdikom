//=============================================================================
/*! _drovector*dssmatrix operator */
inline _drovector operator*(const _drovector& vec, const dssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _drovector&, const dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vec.L!=mat.M){
    std::cerr << "[ERROR] operator*(const _drovector&, const dssmatrix&)"
              << std::endl
              << "These vector and matrix can not make a product."
              << std::endl
              << "Your input was (" << vec.L << ") * ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  drovector newvec(mat.N);
  newvec.zero();
  
  for(int c=0; c<mat.VOL; c++){
    newvec(mat.Jndx[c]) +=vec(mat.Indx[c])*mat.Array[c];
  }
  
  vec.destroy();
  return _(newvec);
}
