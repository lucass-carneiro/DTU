"""Compiles the GDD using pandoc.

Usage:
  compile.py [--no-pdf] [--ebook] [--html]
  compile.py (-h | --help)
  compile.py --version

Options:
  -h --help  Show this screen.
  --version  Show version.
  --no-pdf   Don't compile a pdf.
  --ebook    Compile an ebook.
  --html     Compile an HTML website.
"""

import subprocess
import os

from docopt import docopt


def compile_pdf(output_name, chapters):
    """
    Compiles a pdf
    """

    print("Compiling pdf")

    pdf_name = f"{output_name}.pdf"

    pdf_command = [
        "pandoc",
        "-o",
        pdf_name,
        "--pdf-engine=lualatex",
        "--template=templates/pdf.latex",
        "--metadata-file=metadata.yaml",
        "--filter=pandoc-crossref",
    ]

    command = pdf_command + chapters
    return subprocess.Popen(command)


def compile_ebook(output_name, chapters):
    """
    Compiles an ebook
    """

    print("Compiling ebook")

    ebook_name = f"{output_name}.epub"
    cover_image = os.path.join("images", "cover.png")

    ebook_command = [
        "pandoc",
        "-o",
        ebook_name,
        "--template=templates/epub.html",
        f"--epub-cover-image={cover_image}",
        "--metadata-file=metadata.yaml",
        "--filter=pandoc-crossref",
    ]

    command = ebook_command + chapters
    return subprocess.Popen(command)


def compile_html(output_name, chapters):
    """
    Compiles an html document
    """

    print("Compiling html")

    html_name = f"{output_name}.html"

    html_command = [
        "pandoc",
        "-o",
        html_name,
        "--template=templates/html.html",
        "--standalone",
        "--to=html5",
        "--metadata-file=metadata.yaml",
        "--webtex",
        "--filter=pandoc-crossref",
    ]

    command = html_command + chapters
    return subprocess.Popen(command)


def main(args):
    """
    Parse args and dispatch compile commands
    """

    output_name = "DTU_Design_Doc"

    chapters = [
        "chapters/intro.md",
        "chapters/gameplay.md",
        "chapters/mechanics.md",
        "chapters/story.md",
        "chapters/world.md",
        "chapters/characters.md",
        "chapters/levels.md",
        "chapters/user_interface.md",
        "chapters/feedback.md",
        "chapters/deployment.md",
        "chapters/development.md",
        "chapters/references.md",
    ]

    procs = []

    if args["--no-pdf"] is False:
        procs.append(compile_pdf(output_name, chapters))

    if args["--ebook"]:
        procs.append(compile_ebook(output_name, chapters))

    if args["--html"]:
        procs.append(compile_html(output_name, chapters))

    for proc in procs:
        proc.wait()


if __name__ == "__main__":
    arguments = docopt(__doc__, version="GDD Compiler 1.0")
    main(arguments)
