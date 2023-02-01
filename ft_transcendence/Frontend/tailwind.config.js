module.exports = {
    content: [
      "./pages/**/*.{js,ts,jsx,tsx}",
      "./components/**/*.{js,ts,jsx,tsx}",
    ],
    theme: {
      extend: {
        screens: {
          'canvas_xl': {'max': '1279px'},
          // => @media (max-width: 1279px) { ... }
    
          'canvas_lg': {'max': '1023px'},
          // => @media (max-width: 1023px) { ... }
    
          'canvas_md': {'max': '767px'},
          // => @media (max-width: 767px) { ... }
    
          'canvas_sm': {'max': '639px'},
          // => @media (max-width: 639px) { ... }
        },
        colors: {
          '#0C0915': '#0C0915',
          '#CDF2F0': '#CDF2F0',
          '#38E1BB': '#38E1BB',
          '#3D52D5': '#3D52D5',
          '#3C364D': '#3C364D',
        },
        fontFamily:{
          lexend:"'Lexend Peta', serif",
          nanum:"'Nanum Gothic Coding', serif",
        },
      },
    },
    plugins: [],
  }