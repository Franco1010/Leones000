# INSTRUCTIONS: run this code with "python3 snippetGen.py > out.txt" in the root folder
# of Leones000 it will search over all folders and parse all cpp codes into json.
# Do cmd+shift+p or equivalent and go to "Preferences: Configure User Snippets" then look for "cpp.json"
# copy and paste contents from out.txt to cpp.json

import os
import json

def generate_snippets():
    # Diccionario para almacenar los snippets
    snippets_dict = {}

    # Recorre todos los archivos en el directorio actual y sus subcarpetas
    for root, dirs, files in os.walk("../"):
        for file in files:
            if file.endswith(".cpp"):
                # Ruta completa al archivo
                file_path = os.path.join(root, file)

                # Leemos el contenido del archivo
                with open(file_path, "r") as f:
                    content = f.read()

                # Generamos el snippet
                snippet = {
                    "prefix": file,  # El prefijo será el nombre del archivo
                    "body": content.split("\n"),  # El cuerpo es el contenido del archivo
                    "description": f"Snippet for {file}"  # Descripción
                }

                # Agregamos el snippet al diccionario
                snippets_dict[file] = snippet

    # Generamos el archivo de snippets
    with open("cpp_snippets.json", "w") as f:
        json.dump(snippets_dict, f, indent=4)

generate_snippets()
