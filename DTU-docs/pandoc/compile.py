"""Compiles the GDD using pandoc.

Usage:
  compile.py <target-name>...
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
        #"--template=templates/pdf.latex",
        "--metadata-file=metadata.yaml",
        "--filter=pandoc-crossref",
        "--toc",
    ]

    command = pdf_command + chapters
    return subprocess.Popen(command)


def compile_ebook(output_name, chapters):
    """
    Compiles an ebook
    """

    print("Compiling ebook")

    ebook_name = f"{output_name}.epub"
    cover_image = os.path.join("..", "images", "cover.png")

    ebook_command = [
        "pandoc",
        "-o",
        ebook_name,
        "--template=templates/epub.html",
        f"--epub-cover-image={cover_image}",
        "--metadata-file=metadata.yaml",
        "--filter=pandoc-crossref",
        "--toc",
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
        "--toc",
    ]

    command = html_command + chapters
    return subprocess.Popen(command)


def main(args):
    """
    Parse args and dispatch compile commands
    """

    output_name = "DTU_Design_Doc"

    chapters = [
        os.path.join("..", "gdd_chapters", chapter_name)
        for chapter_name in os.listdir(os.path.join("..", "gdd_chapters"))
    ]

    procs = []

    for target_name in args["<target-name>"]:
        if target_name == "pdf":
            procs.append(compile_pdf(output_name, chapters))
        elif target_name == "epub":
            procs.append(compile_ebook(output_name, chapters))
        elif target_name == "html":
            procs.append(compile_html(output_name, chapters))
        else:
            print(f"Unrecognized target: {target_name}. Ignoring")

    for proc in procs:
        proc.wait()


if __name__ == "__main__":
    arguments = docopt(__doc__, version="GDD Compiler 1.0")
    main(arguments)
