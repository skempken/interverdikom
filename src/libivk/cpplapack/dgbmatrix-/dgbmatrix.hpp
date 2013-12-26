//=============================================================================
//! Real Double-precision General Band Matrix Class
class dgbmatrix
{
private:
  //// objects ////
  long M; //!< matrix row size (NOT accessible)
  long N; //!< matrix column size (NOT accessible)
  long KL; //!< lower band width (NOT accessible)
  long KU; //!< upper band width (NOT accessible)
  double* Array; //!< 1D array to store matrix data (NOT accessible)
  double** Darray; //!< array of pointers of column head addresses(NOT accessible)
  
public:
  //// const references ////
  long const& m; //!< matrix row size (readable)
  long const& n; //!< matrix column size (readable)
  long const& kl; //!< lower band width (readable)
  long const& ku; //!< upper band width (readable)
  double* const& array; //!< 1D array to store matrix data (readable)
  double** const& darray; //!< array of pointers of column head addresses (readable)
  
  //// constructor ////
  inline dgbmatrix();
  inline dgbmatrix(const dgbmatrix&);
  inline dgbmatrix(const _dgbmatrix&);
  inline dgbmatrix(const long&, const long&, const long&, const long&);
  inline dgbmatrix(const char *);
  inline ~dgbmatrix(); //destructor
  
  //// cast ////
  inline operator _zgbmatrix();
  
  //// io ////
  inline double& operator()(const long&, const long&);
  inline double operator()(const long&, const long&) const;
  inline void set(const long&, const long&, const double&) const;
  inline friend std::ostream& operator<<(std::ostream&, const dgbmatrix&);
  inline void write(const char *) const;
  inline void read(const char *);
  
  //// misc ////
  inline void clear();
  inline void zero();
  inline void identity();
  inline void chsign();
  inline void copy(const dgbmatrix&);
  inline void shallow_copy(const _dgbmatrix&);
  inline void resize(const long&, const long&, const long&, const long&);
  inline friend void swap(dgbmatrix&, dgbmatrix&);
  inline friend _dgbmatrix _(dgbmatrix&);
  
  //// calc ////
  inline friend _dgbmatrix t(const dgbmatrix&);
  inline friend _dgematrix i(const dgbmatrix&);
  
  //// lapack ////
  inline long dgbsv(dgematrix&);
  inline long dgbsv(dcovector&);
  
  //// unary ////
  inline friend const dgbmatrix& operator+(const dgbmatrix&);
  inline friend _dgbmatrix operator-(const dgbmatrix&);
  
  //// operators with dgbmatrix ////
  inline dgbmatrix& operator=(const dgbmatrix&);
  inline dgbmatrix& operator+=(const dgbmatrix&);
  inline dgbmatrix& operator-=(const dgbmatrix&);
  inline dgbmatrix& operator*=(const dgbmatrix&);
  //// operators with _dgbmatrix ////
  inline dgbmatrix& operator=(const _dgbmatrix&);
  inline dgbmatrix& operator+=(const _dgbmatrix&);
  inline dgbmatrix& operator-=(const _dgbmatrix&);
  inline dgbmatrix& operator*=(const _dgbmatrix&);
  
  //// operators with double ////
  inline dgbmatrix& operator*=(const double&);
  inline dgbmatrix& operator/=(const double&);
  
  //// + ////
  inline friend _dgbmatrix operator+(const  dgbmatrix&, const  dgbmatrix&);
  inline friend _dgbmatrix operator+(const  dgbmatrix&, const _dgbmatrix&);
  inline friend _dgbmatrix operator+(const _dgbmatrix&, const  dgbmatrix&);
  
  inline friend _dgematrix operator+(const  dgbmatrix&, const  dgematrix&);
  inline friend _dgematrix operator+(const  dgbmatrix&, const _dgematrix&);
  inline friend _dgematrix operator+(const  dgematrix&, const  dgbmatrix&);
  inline friend _dgematrix operator+(const _dgematrix&, const  dgbmatrix&);
  
  inline friend _dgematrix operator+(const  dgbmatrix&, const  dsymatrix&);
  inline friend _dgematrix operator+(const  dgbmatrix&, const _dsymatrix&);
  inline friend _dgematrix operator+(const  dsymatrix&, const  dgbmatrix&);
  inline friend _dgematrix operator+(const _dsymatrix&, const  dgbmatrix&);

  inline friend _dgematrix operator+(const  dgbmatrix&, const  dssmatrix&);
  inline friend _dgematrix operator+(const  dgbmatrix&, const _dssmatrix&);
  inline friend _dgematrix operator+(const  dssmatrix&, const  dgbmatrix&);
  inline friend _dgematrix operator+(const _dssmatrix&, const  dgbmatrix&);
  
  //// - ////
  inline friend _dgbmatrix operator-(const  dgbmatrix&, const  dgbmatrix&);
  inline friend _dgbmatrix operator-(const  dgbmatrix&, const _dgbmatrix&);
  inline friend _dgbmatrix operator-(const _dgbmatrix&, const  dgbmatrix&);
  
  inline friend _dgematrix operator-(const  dgbmatrix&, const  dgematrix&);
  inline friend _dgematrix operator-(const  dgbmatrix&, const _dgematrix&);
  inline friend _dgematrix operator-(const  dgematrix&, const  dgbmatrix&);
  inline friend _dgematrix operator-(const _dgematrix&, const  dgbmatrix&); 
  
  inline friend _dgematrix operator-(const  dgbmatrix&, const  dsymatrix&);
  inline friend _dgematrix operator-(const  dgbmatrix&, const _dsymatrix&);
  inline friend _dgematrix operator-(const  dsymatrix&, const  dgbmatrix&);
  inline friend _dgematrix operator-(const _dsymatrix&, const  dgbmatrix&); 

  inline friend _dgematrix operator-(const  dgbmatrix&, const  dssmatrix&);
  inline friend _dgematrix operator-(const  dgbmatrix&, const _dssmatrix&);
  inline friend _dgematrix operator-(const  dssmatrix&, const  dgbmatrix&);
  inline friend _dgematrix operator-(const _dssmatrix&, const  dgbmatrix&); 
  
  //// * ////
  inline friend _dgbmatrix operator*(const  dgbmatrix&, const  dgbmatrix&);
  inline friend _dgbmatrix operator*(const  dgbmatrix&, const _dgbmatrix&);
  inline friend _dgbmatrix operator*(const _dgbmatrix&, const  dgbmatrix&);

  inline friend _dgematrix operator*(const  dgbmatrix&, const  dgematrix&);
  inline friend _dgematrix operator*(const  dgbmatrix&, const _dgematrix&);
  inline friend _dgematrix operator*(const  dgematrix&, const  dgbmatrix&);
  inline friend _dgematrix operator*(const _dgematrix&, const  dgbmatrix&);
  
  inline friend _dgematrix operator*(const  dgbmatrix&, const  dsymatrix&);
  inline friend _dgematrix operator*(const  dgbmatrix&, const _dsymatrix&);
  inline friend _dgematrix operator*(const  dsymatrix&, const  dgbmatrix&);
  inline friend _dgematrix operator*(const _dsymatrix&, const  dgbmatrix&);

  inline friend _dgematrix operator*(const  dgbmatrix&, const  dssmatrix&);
  inline friend _dgematrix operator*(const  dgbmatrix&, const _dssmatrix&);
  inline friend _dgematrix operator*(const  dssmatrix&, const  dgbmatrix&);
  inline friend _dgematrix operator*(const _dssmatrix&, const  dgbmatrix&);
  
  inline friend _dcovector operator*(const  dgbmatrix&, const  dcovector&);
  inline friend _dcovector operator*(const  dgbmatrix&, const _dcovector&);
  
  inline friend _drovector operator*(const  drovector&, const  dgbmatrix&);
  inline friend _drovector operator*(const _drovector&, const  dgbmatrix&);
  
  inline friend _dgbmatrix operator*(const  dgbmatrix&, const     double&);
  inline friend _dgbmatrix operator*(const     double&, const  dgbmatrix&);
  
  //// / ////
  inline friend _dgbmatrix operator/(const  dgbmatrix&, const     double&);
  
  //// friend classes ////
  friend class  dgematrix;
  friend class _dgematrix;
  friend class _dgbmatrix;
  friend class  dsymatrix;
  friend class _dsymatrix;
  friend class  dssmatrix;
  friend class _dssmatrix;
  friend class  dcovector;
  friend class _dcovector;
  friend class  drovector;
  friend class _drovector;
};
