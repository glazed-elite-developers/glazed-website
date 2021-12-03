const path = require('path')

exports.onCreateWebpackConfig = ({ actions }) => {
  actions.setWebpackConfig({
    resolve: {
      alias: {
        re: path.resolve(__dirname, 'lib/es6/re'),
        src: path.resolve(__dirname, 'src'),
        static: path.resolve(__dirname, 'static'),
      },
    },
  })
}
