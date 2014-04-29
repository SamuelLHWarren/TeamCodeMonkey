/*global module:false*/
module.exports = function(grunt) {
  "use strict";

  // Project configuration.
  grunt.initConfig({
    // Metadata.
    pkg: grunt.file.readJSON('package.json'),
    banner: '/*! <%= pkg.title || pkg.name %> - v<%= pkg.version %> - ' +
      '<%= grunt.template.today("yyyy-mm-dd") %>\n' +
      '<%= pkg.homepage ? "* " + pkg.homepage + "\\n" : "" %>' +
      '* Copyright (c) <%= grunt.template.today("yyyy") %> <%= pkg.author.name %>;' +
      ' Licensed <%= _.pluck(pkg.licenses, "type").join(", ") %> */\n',
    // Task configuration.
    recess: {
      dist: {
        options: {
          compile: true,
        },
      src: 'less/base.styles.less',
      dest: 'css/base.styles.css'
      }
    },
    watch: {
      options: {
        livereload: true
      },
      styles: {
        files: 'less/*.less',
        tasks: ['recess:dist']
      }
    },
    copy: {
      dist:{
        files: [
          {expand: true, src: ['css/**', 'less/**', 'Gruntfile.js', 'images/**', 'js/**', 'logo.png', 'package.json', 'README.md', 'screenshot.png', 'template.php', 'templates/**', 'theme-settings.php', 'wvus.uikit', 'wvusdrupal.info'], dest: '../<%= pkg.name %>/wvusdrupal'},
          {expand: true, cwd: '../wvus-subtheme', src: ['css/**', 'Gruntfile.js', 'images/**', 'js/**', 'less/**', 'package.json', 'template.php', 'templates/**', 'wvus-subtheme.info'], dest: '../<%= pkg.name %>/wvus-subtheme'}
        ]
      }
    },
    compress: {
      dist: {
        options: {
          mode: 'zip',
          archive: '../<%= pkg.name %>-<%= pkg.version %>.zip'
        },
        files: [
          {expand: true, cwd: '../', src: ['<%= pkg.name %>/**'], dest: '../'}
        ]
      }
    },
    clean: {
      options:{
        force: true
      },
      src: '../<%= pkg.name %>',
    }
  });

  // These plugins provide necessary tasks.

  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.loadNpmTasks('grunt-contrib-copy');
  grunt.loadNpmTasks('grunt-recess');
  grunt.loadNpmTasks('grunt-contrib-compress');
  grunt.loadNpmTasks('grunt-contrib-clean');


  // Default task.
  grunt.registerTask('default', ['watch']);
  grunt.registerTask('build', ['copy','compress', 'clean']);

};
