//=============================================================================
//! Real Double-precision General Dence Matrix Class
class dgematrix
{
private:
  //// objects ////
  long M; //!< matrix row size (NOT accessible)
  long N; //!< matrix column size (NOT accessible)
  double* Array; //!< 1D array to store matrix data (NOT accessible)
  double** Darray; //!< array of pointers of column head addresses(NOT accessible)
  
public:
  //// const references ////
  long const& m; //!< matrix row size (readable)
  long const& n; //!< matrix column size (readable)
  double* const& array; //!< 1D array to store matrix data (readable)
  double** const& darray; //!< array of pointers of column head addresses (readable)
  
  //// constructor ////
  inline dgematrix();
  inline dgematrix(const dgematrix&);
  inline dgematrix(const _dgematrix&);
  inline dgematrix(const dgbmatrix&);
  inline dgematrix(const _dgbmatrix&);
  inline dgematrix(const dsymatrix&);
  inline dgematrix(const _dsymatrix&);
  inline dgematrix(const dssmatrix&);
  inline dgematrix(const _dssmatrix&);
  inline dgematrix(const long&, const long&);
  inline dgematrix(const char*);
  inline ~dgematrix(); //destructor
  
  //// cast ////
  inline operator _zgematrix();
  
  //// io ////
  inline double& operator()(const long&, const long&);
  inline double operator()(const long&, const long&) const;
  inline void set(const long&, const long&, const double&) const;
  inline friend std::ostream& operator<<(std::ostream&, const dgematrix&);
  inline void write(const char *) const;
  inline void read(const char *);

  //// misc ////
  inline void clear();
  inline void zero();
  inline void identity();
  inline void chsign();
  inline void copy(const dgematrix&);
  inline void shallow_copy(const _dgematrix&);
  inline void resize(const long&, const long&);
  inline friend void swap(dgematrix&, dgematrix&);
  inline friend _dgematrix _(dgematrix&);
  
  //// calc ////
  inline friend _dgematrix t(const dgematrix&);
  inline friend _dgematrix i(const dgematrix&);
  inline friend void idamax(long&, long&, const dgematrix&);
  inline friend double damax(const dgematrix&);
  
  //// lapack ////
  inline long dgesv(dgematrix&);
  inline long dgesv(dcovector&);
  inline long dgels(dgematrix&);
  inline long dgels(dcovector&);
  inline long dgels(dgematrix&, drovector&);
  inline long dgels(dcovector&, double&);
  inline long dgelss(dcovector&, dcovector&, long&, const double);
  inline long dgelss(dgematrix&, dcovector&, long&, const double);
  inline long dgeev(std::vector<double>&, std::vector<double>&);
  inline long dgeev(std::vector<double>&, std::vector<double>&, 
                    std::vector<dcovector>&, std::vector<dcovector>&);
  inline long dgeev(std::vector<double>&, std::vector<double>&, 
                    std::vector<drovector>&, std::vector<drovector>&);
  inline long dggev(dgematrix&, std::vector<double>&, std::vector<double>&);
  inline long dggev(dgematrix&, std::vector<double>&, std::vector<double>&,
                    std::vector<dcovector>&, std::vector<dcovector>&);
  inline long dggev(dgematrix&, std::vector<double>&, std::vector<double>&,
                    std::vector<drovector>&, std::vector<drovector>&);
  inline long dgesvd(dcovector&, dgematrix&, dgematrix&);
  
  //// unary ////
  inline friend const dgematrix& operator+(const dgematrix&);
  inline friend _dgematrix operator-(const dgematrix&);
  
  //// operators with dgematrix ////
  inline dgematrix& operator=(const dgematrix&);
  inline dgematrix& operator+=(const dgematrix&);
  inline dgematrix& operator-=(const dgematrix&);
  inline dgematrix& operator*=(const dgematrix&);
  //// operators with _dgematrix ////
  inline dgematrix& operator=(const _dgematrix&);
  inline dgematrix& operator+=(const _dgematrix&);
  inline dgematrix& operator-=(const _dgematrix&);
  inline dgematrix& operator*=(const _dgematrix&);
  //// operators with dgbmatrix ////
  inline dgematrix& operator=(const dgbmatrix&);
  inline dgematrix& operator+=(const dgbmatrix&);
  inline dgematrix& operator-=(const dgbmatrix&);
  inline dgematrix& operator*=(const dgbmatrix&);
  //// operators with _dgbmatrix ////
  inline dgematrix& operator=(const _dgbmatrix&);
  inline dgematrix& operator+=(const _dgbmatrix&);
  inline dgematrix& operator-=(const _dgbmatrix&);
  inline dgematrix& operator*=(const _dgbmatrix&);
  //// operators with dsymatrix ////
  inline dgematrix& operator=(const dsymatrix& mat);
  inline dgematrix& operator+=(const dsymatrix& mat);
  inline dgematrix& operator-=(const dsymatrix& mat);
  inline dgematrix& operator*=(const dsymatrix& mat);
  //// operators with _dsymatrix ////
  inline dgematrix& operator=(const _dsymatrix& mat);
  inline dgematrix& operator+=(const _dsymatrix& mat);
  inline dgematrix& operator-=(const _dsymatrix& mat);
  inline dgematrix& operator*=(const _dsymatrix& mat);

  //// operators with double ////
  inline dgematrix& operator*=(const double&);
  inline dgematrix& operator/=(const double&);

  //// + ////
  inline friend _dgematrix operator+(const  dgematrix&, const  dgematrix&);
  inline friend _dgematrix operator+(const  dgematrix&, const _dgematrix&);
  inline friend _dgematrix operator+(const _dgematrix&, const  dgematrix&);
  
  inline friend _dgematrix operator+(const  dgematrix&, const  dgbmatrix&);
  inline friend _dgematrix operator+(const  dgematrix&, const _dgbmatrix&);
  inline friend _dgematrix operator+(const  dgbmatrix&, const  dgematrix&);
  inline friend _dgematrix operator+(const _dgbmatrix&, const  dgematrix&);
  
  inline friend _dgematrix operator+(const  dgematrix&, const  dsymatrix&);
  inline friend _dgematrix operator+(const  dgematrix&, const _dsymatrix&);
  inline friend _dgematrix operator+(const  dsymatrix&, const  dgematrix&);
  inline friend _dgematrix operator+(const _dsymatrix&, const  dgematrix&);

  inline friend _dgematrix operator+(const  dgematrix&, const  dssmatrix&);
  inline friend _dgematrix operator+(const  dgematrix&, const _dssmatrix&);
  inline friend _dgematrix operator+(const  dssmatrix&, const  dgematrix&);
  inline friend _dgematrix operator+(const _dssmatrix&, const  dgematrix&);
  
  //// - ////
  inline friend _dgematrix operator-(const  dgematrix&, const  dgematrix&);
  inline friend _dgematrix operator-(const  dgematrix&, const _dgematrix&);
  inline friend _dgematrix operator-(const _dgematrix&, const  dgematrix&);
  
  inline friend _dgematrix operator-(const  dgematrix&, const  dgbmatrix&);
  inline friend _dgematrix operator-(const  dgematrix&, const _dgbmatrix&);
  inline friend _dgematrix operator-(const  dgbmatrix&, const  dgematrix&);
  inline friend _dgematrix operator-(const _dgbmatrix&, const  dgematrix&);
  
  inline friend _dgematrix operator-(const  dgematrix&, const  dsymatrix&);
  inline friend _dgematrix operator-(const  dgematrix&, const _dsymatrix&);
  inline friend _dgematrix operator-(const  dsymatrix&, const  dgematrix&);
  inline friend _dgematrix operator-(const _dsymatrix&, const  dgematrix&);
  
  inline friend _dgematrix operator-(const  dgematrix&, const  dssmatrix&);
  inline friend _dgematrix operator-(const  dgematrix&, const _dssmatrix&);
  inline friend _dgematrix operator-(const  dssmatrix&, const  dgematrix&);
  inline friend _dgematrix operator-(const _dssmatrix&, const  dgematrix&);
  
  //// * ////
  inline friend _dgematrix operator*(const  dgematrix&, const  dgematrix&);
  inline friend _dgematrix operator*(const  dgematrix&, const _dgematrix&);
  inline friend _dgematrix operator*(const _dgematrix&, const  dgematrix&);
  
  inline friend _dgematrix operator*(const  dgematrix&, const  dgbmatrix&);
  inline friend _dgematrix operator*(const  dgematrix&, const _dgbmatrix&);  
  inline friend _dgematrix operator*(const  dgbmatrix&, const  dgematrix&);
  inline friend _dgematrix operator*(const _dgbmatrix&, const  dgematrix&);
  
  inline friend _dgematrix operator*(const  dsymatrix&, const  dgematrix&);
  inline friend _dgematrix operator*(const _dsymatrix&, const  dgematrix&);
  inline friend _dgematrix operator*(const  dgematrix&, const  dsymatrix&);
  inline friend _dgematrix operator*(const  dgematrix&, const _dsymatrix&);

  inline friend _dgematrix operator*(const  dssmatrix&, const  dgematrix&);
  inline friend _dgematrix operator*(const _dssmatrix&, const  dgematrix&);
  inline friend _dgematrix operator*(const  dgematrix&, const  dssmatrix&);
  inline friend _dgematrix operator*(const  dgematrix&, const _dssmatrix&);

  inline friend _dcovector operator*(const  dgematrix&, const  dcovector&);
  inline friend _dcovector operator*(const  dgematrix&, const _dcovector&);
  
  inline friend _drovector operator*(const  drovector&, const  dgematrix&);
  inline friend _drovector operator*(const _drovector&, const  dgematrix&);
  
  inline friend _dgematrix operator*(const  dgematrix&, const     double&);
  inline friend _dgematrix operator*(const     double&, const  dgematrix&);
  
  //// / ////
  inline friend _dgematrix operator/(const  dgematrix&, const     double&);

  //// friend classes ////
  friend class _dgematrix;
  friend class  dgbmatrix;
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
