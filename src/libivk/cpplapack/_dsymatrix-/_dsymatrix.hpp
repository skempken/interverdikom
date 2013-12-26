//=============================================================================
//! (DO NOT USE) Smart-temporary Real Double-precision Symmetric Matrix Class
class _dsymatrix
{
public:
  //// objects ////
  mutable long N; //!< matrix column or row size
  mutable double* Array; //!< 1D Array to store matrix data
  mutable double** Darray; //!< array of pointers of column head addresses
  
  //// constructor ////
  inline _dsymatrix();
  inline _dsymatrix(const _dsymatrix&);
  inline ~_dsymatrix(); //destructor
  
  //// cast ////
  inline operator _zhematrix();
  
  //// io ////
  inline double& operator()(const long&, const long&) const;
  inline friend std::ostream& operator<<(std::ostream&, const dsymatrix&);
  inline void write(const char *) const;
  
  //// misc ////
  inline void destroy() const;
  inline void complete() const;
  
  //// calc ////
  inline friend _dsymatrix t(const _dsymatrix&);
  inline friend _dgematrix i(const _dsymatrix&);
  
  //// unary ////
  inline friend const _dsymatrix& operator+(const _dsymatrix&);
  inline friend _dsymatrix operator-(const _dsymatrix&);
  
  //// + ////
  inline friend _dsymatrix operator+(const  dsymatrix&, const  dsymatrix&);
  inline friend _dsymatrix operator+(const  dsymatrix&, const _dsymatrix&);
  inline friend _dsymatrix operator+(const _dsymatrix&, const  dsymatrix&);
  inline friend _dsymatrix operator+(const _dsymatrix&, const _dsymatrix&);
  
  inline friend _dgematrix operator+(const _dsymatrix&, const  dgematrix&);
  inline friend _dgematrix operator+(const _dsymatrix&, const _dgematrix&);
  inline friend _dgematrix operator+(const  dgematrix&, const _dsymatrix&);
  inline friend _dgematrix operator+(const _dgematrix&, const _dsymatrix&);
  
  inline friend _dgematrix operator+(const _dsymatrix&, const  dgbmatrix&);
  inline friend _dgematrix operator+(const _dsymatrix&, const _dgbmatrix&);
  inline friend _dgematrix operator+(const  dgbmatrix&, const _dsymatrix&);
  inline friend _dgematrix operator+(const _dgbmatrix&, const _dsymatrix&);
  
  //// - ////
  inline friend _dsymatrix operator-(const  dsymatrix&, const  dsymatrix&);
  inline friend _dsymatrix operator-(const  dsymatrix&, const _dsymatrix&);
  inline friend _dsymatrix operator-(const _dsymatrix&, const  dsymatrix&);
  inline friend _dsymatrix operator-(const _dsymatrix&, const _dsymatrix&);
  
  inline friend _dgematrix operator-(const _dsymatrix&, const  dgematrix&);  
  inline friend _dgematrix operator-(const _dsymatrix&, const _dgematrix&);
  inline friend _dgematrix operator-(const  dgematrix&, const _dsymatrix&);
  inline friend _dgematrix operator-(const _dgematrix&, const _dsymatrix&);
  
  inline friend _dgematrix operator-(const _dsymatrix&, const  dgbmatrix&);  
  inline friend _dgematrix operator-(const _dsymatrix&, const _dgbmatrix&);
  inline friend _dgematrix operator-(const  dgbmatrix&, const _dsymatrix&);
  inline friend _dgematrix operator-(const _dgbmatrix&, const _dsymatrix&);
  
  //// * ////
  inline friend _dgematrix operator*(const _dsymatrix&, const  dgematrix&);
  inline friend _dgematrix operator*(const _dsymatrix&, const _dgematrix&);
  inline friend _dgematrix operator*(const  dgematrix&, const _dsymatrix&);
  inline friend _dgematrix operator*(const _dgematrix&, const _dsymatrix&);
  
  inline friend _dgematrix operator*(const _dsymatrix&, const  dgbmatrix&);
  inline friend _dgematrix operator*(const _dsymatrix&, const _dgbmatrix&);
  inline friend _dgematrix operator*(const  dgbmatrix&, const _dsymatrix&);
  inline friend _dgematrix operator*(const _dgbmatrix&, const _dsymatrix&);
  
  inline friend _dgematrix operator*(const _dsymatrix&, const  dsymatrix&);
  inline friend _dgematrix operator*(const  dsymatrix&, const _dsymatrix&);
  inline friend _dgematrix operator*(const _dsymatrix&, const _dsymatrix&);

  inline friend _dsymatrix operator*(const  dsymatrix&, const     double&);
  inline friend _dsymatrix operator*(const _dsymatrix&, const     double&);
  inline friend _dsymatrix operator*(const     double&, const  dsymatrix&);
  inline friend _dsymatrix operator*(const     double&, const _dsymatrix&);
  
  inline friend _drovector operator*(const  drovector&, const _dsymatrix&);
  inline friend _drovector operator*(const _drovector&, const _dsymatrix&);
  inline friend _dcovector operator*(const _dsymatrix&, const  dcovector&);
  inline friend _dcovector operator*(const _dsymatrix&, const _dcovector&);
  
  //// / ////
  inline friend _dsymatrix operator/(const  dsymatrix&, const     double&);
  inline friend _dsymatrix operator/(const _dsymatrix&, const     double&);
  
  //// friend classes ////
  friend class  dgematrix;
  friend class _dgematrix;
  friend class  dgbmatrix;
  friend class _dgbmatrix;
  friend class  dsymatrix;
  friend class  dcovector;
  friend class _dcovector;
  friend class  drovector;
  friend class _drovector;
};
