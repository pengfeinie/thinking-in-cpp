# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))


# -- Project information -----------------------------------------------------

project = 'thinking-in-cpp'
copyright = '2023, pfnie'
author = 'pfnie'

# The full version, including alpha/beta/rc tags
release = 'v0.0.1'


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
     'recommonmark',
     'sphinx_markdown_tables',
     'sphinxcontrib.video',
     'sphinx.ext.autodoc',
     'sphinx.ext.viewcode',
     'sphinx.ext.githubpages',
     'rst2pdf.pdfbuilder'
 ]

# Add any paths that contain templates here, relative to this directory.
#templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = []


# add "Edit on Github"
html_context = {
	"display_github": True,
	"github_user":"pengfeinie",
	"github_repo":"thinking-in-cpp",
	"github_version":"main/source/"
}

# -- Options for PDF output --------------------------------------------------

pdf_documents = [
    ('index', 'thinking-in-cpp', 'thinking-in-cpp', 'pfnie'),
]

pdf_stylesheets = ['sphinx', 'kerning', 'a4']
pdf_language = "en_US"

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

# If true, links to the reST sources are added to the pages.
#
html_show_sourcelink = True

# If true, "Created using Sphinx" is shown in the HTML footer. Default is True.
#
html_show_sphinx = True

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
html_css_files = [
    'custom.css',
]

# If true, links to the reST sources are added to the pages.
#
html_show_sourcelink = True

# If true, "Created using Sphinx" is shown in the HTML footer. Default is True.
#
html_show_sphinx = True

html_theme_options = {
   'navigation_depth': 4, #根据实际需求调整
       'collapse_navigation': False,
    'sticky_navigation': True,
}

