//=============================================================================
//! (DO NOT USE) Smart-temporary Real Double-precision General Band Matrix Class
class _dgbmatrix
{
public:
  //// objects ////
  mutable long M; //!< matrix row size
  mutable long N; //!< matrix column size
  mutable long KL; //!< lower band width 
  mutable long KU; //!< upper band width 
  mutable double* Array; //!< 1D Array to store matrix data
  mutable double** Darray; //!< array of pointers of column head addresses
  
  //// constructor ////
  inline _dgbmatrix();
  inline _dgbmatrix(const _dgbmatrix&);
  inline ~_dgbmatrix(); //destructor
  
  //// cast ////
  inline operator _zgbmatrix();
  
  //// io ////
  inline double& operator()(const long&, const long&) const;
  inline friend std::ostream& operator<<(std::ostream&, const _dgbmatrix&);
  inline void write(const char *) const;
  
  //// misc ////
  inline void destroy() const;
  
  //// calc ////
  inline friend _dgbmatrix t(const _dgbmatrix&);
  inline friend _dgematrix i(const _dgbmatrix&);
  
  //// unary ////
  inline friend const _dgbmatrix& operator+(const _dgbmatrix&);
  inline friend _dgbmatrix operator-(const _dgbmatrix&);
  
  //// + ////
  inline friend _dgbmatrix operator+(const  dgbmatrix&, const  dgbmatrix&);
  inline friend _dgbmatrix operator+(const  dgbmatrix&, const _dgbmatrix&);
  inline friend _dgbmatrix operator+(const _dgbmatrix&, const  dgbmatrix&);
  inline friend _dgbmatrix operator+(const _dgbmatrix&, const _dgbmatrix&);
  
  inline friend _dgematrix operator+(const _dgbmatrix&, const  dgematrix&);
  inline friend _dgematrix operator+(const _dgbmatrix&, const _dgematrix&);
  inline friend _dgematrix operator+(const  dgematrix&, const _dgbmatrix&);
  inline friend _dgematrix operator+(const _dgematrix&, const _dgbmatrix&);
  
  inline friend _dgematrix operator+(const _dgbmatrix&, const  dsymatrix&);
  inline friend _dgematrix operator+(const _dgbmatrix&, const _dsymatrix&);
  inline friend _dgematrix operator+(const  dsymatrix&, const _dgbmatrix&);
  inline friend _dgematrix operator+(const _dsymatrix&, const _dgbmatrix&);
  
  //// - ////
  inline friend _dgbmatrix operator-(const  dgbmatrix&, const  dgbmatrix&);
  inline friend _dgbmatrix operator-(const  dgbmatrix&, const _dgbmatrix&);
  inline friend _dgbmatrix operator-(const _dgbmatrix&, const  dgbmatrix&);
  inline friend _dgbmatrix operator-(const _dgbmatrix&, const _dgbmatrix&);
  
  inline friend _dgematrix operator-(const _dgbmatrix&, const  dgematrix&);
  inline friend _dgematrix operator-(const _dgbmatrix&, const _dgematrix&);
  inline friend _dgematrix operator-(const  dgematrix&, const _dgbmatrix&);
  inline friend _dgematrix operator-(const _dgematrix&, const _dgbmatrix&);
  
  inline friend _dgematrix operator-(const _dgbmatrix&, const  dsymatrix&);
  inline friend _dgematrix operator-(const _dgbmatrix&, const _dsymatrix&);
  inline friend _dgematrix operator-(const  dsymatrix&, const _dgbmatrix&);
  inline friend _dgematrix operator-(const _dsymatrix&, const _dgbmatrix&);
  
  //// * ////
  inline friend _dgbmatrix operator*(const  dgbmatrix&, const  dgbmatrix&);
  inline friend _dgbmatrix operator*(const  dgbmatrix&, const _dgbmatrix&);
  inline friend _dgbmatrix operator*(const _dgbmatrix&, const  dgbmatrix&);
  inline friend _dgbmatrix operator*(const _dgbmatrix&, const _dgbmatrix&);
  
  inline friend _dgbmatrix operator*(const  dgbmatrix&, const     double&);
  inline friend _dgbmatrix operator*(const _dgbmatrix&, const     double&);
  inline friend _dgbmatrix operator*(const     double&, const  dgbmatrix&);
  inline friend _dgbmatrix operator*(const     double&, const _dgbmatrix&);

  inline friend _dgematrix operator*(const _dgbmatrix&, const  dgematrix&);
  inline friend _dgematrix operator*(const _dgbmatrix&, const _dgematrix&);
  inline friend _dgematrix operator*(const  dgematrix&, const _dgbmatrix&);
  inline friend _dgematrix operator*(const _dgematrix&, const _dgbmatrix&);
  
  inline friend _dgematrix operator*(const _dgbmatrix&, const  dsymatrix&);
  inline friend _dgematrix operator*(const _dgbmatrix&, const _dsymatrix&);
  inline friend _dgematrix operator*(const  dsymatrix&, const _dgbmatrix&);
  inline friend _dgematrix operator*(const _dsymatrix&, const _dgbmatrix&);
  
  inline friend _dcovector operator*(const _dgbmatrix&, const  dcovector&);
  inline friend _dcovector operator*(const _dgbmatrix&, const _dcovector&);
  inline friend _drovector operator*(const  drovector&, const _dgbmatrix&);
  inline friend _drovector operator*(const _drovector&, const _dgbmatrix&);
  
  //// / ////
  inline friend _dgbmatrix operator/(const  dgbmatrix&, const     double&);
  inline friend _dgbmatrix operator/(const _dgbmatrix&, const     double&);
  
  //// friend classes ////
  friend class  dgematrix;
  friend class _dgematrix;
  friend class  dgbmatrix;
  friend class  dsymatrix;
  friend class _dsymatrix;
  friend class  dcovector;
  friend class _dcovector;
  friend class  drovector;
  friend class _drovector;
};
