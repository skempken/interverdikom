//=============================================================================
//! (DO NOT USE) Smart-temporary Real Double-precision Row Vector Class
class _drovector
{
public:
  //// objects ////
  mutable long L; //!< vector size
  mutable double* Array; //!< 1D Array to store vector data
  
  //// constructor ////
  inline _drovector();
  inline _drovector(const _drovector&);
  inline ~_drovector(); //destructor
  
  //// cast ////
  inline operator _zrovector();
  
  //// io ////
  inline double& operator()(const long&) const;
  inline friend std::ostream& operator<<(std::ostream&, const _drovector&);
  inline void write(const char *) const;
  
  //// calc ////
  inline friend _dcovector t(const drovector&);
  inline friend double nrm2(const drovector&);
  inline friend long idamax(const drovector&);
  inline friend double damax(const drovector&);

  //// misc ////
  inline void destroy() const;
  
  //// unary ////
  inline friend const _drovector& operator+(const _drovector&);
  inline friend _drovector operator-(const _drovector&);
  
  //// + ////
  inline friend _drovector operator+(const  drovector&, const  drovector&);
  inline friend _drovector operator+(const  drovector&, const _drovector&);
  inline friend _drovector operator+(const _drovector&, const  drovector&);
  inline friend _drovector operator+(const _drovector&, const _drovector&);
  
  //// - ////
  inline friend _drovector operator-(const  drovector&, const  drovector&);
  inline friend _drovector operator-(const  drovector&, const _drovector&);
  inline friend _drovector operator-(const _drovector&, const  drovector&);
  inline friend _drovector operator-(const _drovector&, const _drovector&);
  
  //// * ////
  inline friend _drovector operator*(const  drovector&, const  dgematrix&);
  inline friend _drovector operator*(const  drovector&, const _dgematrix&);
  inline friend _drovector operator*(const _drovector&, const  dgematrix&);
  inline friend _drovector operator*(const _drovector&, const _dgematrix&);
  
  inline friend _drovector operator*(const  drovector&, const  dgbmatrix&);
  inline friend _drovector operator*(const  drovector&, const _dgbmatrix&);
  inline friend _drovector operator*(const _drovector&, const  dgbmatrix&);
  inline friend _drovector operator*(const _drovector&, const _dgbmatrix&);
  
  inline friend _drovector operator*(const  drovector&, const  dsymatrix&);
  inline friend _drovector operator*(const  drovector&, const _dsymatrix&);
  inline friend _drovector operator*(const _drovector&, const  dsymatrix&);
  inline friend _drovector operator*(const _drovector&, const _dsymatrix&);

  inline friend _drovector operator*(const  drovector&, const  dssmatrix&);
  inline friend _drovector operator*(const  drovector&, const _dssmatrix&);
  inline friend _drovector operator*(const _drovector&, const  dssmatrix&);
  inline friend _drovector operator*(const _drovector&, const _dssmatrix&);
  
  inline friend _drovector operator*(const     double&, const  drovector&);
  inline friend _drovector operator*(const     double&, const _drovector&);
  inline friend _drovector operator*(const  drovector&, const     double&);
  inline friend _drovector operator*(const _drovector&, const     double&);
  
  inline friend _dgematrix operator*(const  dcovector&, const _drovector&);
  inline friend _dgematrix operator*(const _dcovector&, const _drovector&);
  inline friend     double operator*(const _drovector&, const  dcovector&);
  inline friend     double operator*(const _drovector&, const _dcovector&);
  
  //// / ////
  inline friend _drovector operator/(const  drovector&, const     double&);
  inline friend _drovector operator/(const _drovector&, const     double&);
  
  //// % ////
  inline friend     double operator%(const  drovector&, const _drovector&);
  inline friend     double operator%(const _drovector&, const  drovector&);
  inline friend     double operator%(const _drovector&, const _drovector&);
  
  //// friend classes ////
  friend class  dgematrix;
  friend class _dgematrix;
  friend class  dgbmatrix;
  friend class _dgbmatrix;
  friend class  dsymatrix;
  friend class _dsymatrix;
  friend class  dcovector;
  friend class _dcovector;
  friend class  drovector;
};
