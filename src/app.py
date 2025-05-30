from flask import Flask, render_template, request, redirect, send_from_directory
import os
import subprocess

app = Flask(__name__)

# Folder where files are saved
UPLOAD_FOLDER = os.path.abspath(os.path.dirname(__file__))
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        if 'astfile' not in request.files:
            return 'No file part', 400
        file = request.files['astfile']
        if file.filename == '':
            return 'No selected file', 400
        if file:
            # Save file as output.txt in current folder
            file_path = os.path.join(app.config['UPLOAD_FOLDER'], 'output.txt')
            file.save(file_path)

            try:
                # Run the AST visualizer
                subprocess.run(['python', 'ast_visualizer.py'], check=True)
                return redirect('/result')
            except subprocess.CalledProcessError as e:
                return f"Error running visualizer: {str(e)}", 500

    return render_template('index.html')

@app.route('/result')
def result():
    try:
        # Read AST sections from output.txt
        with open('output.txt', 'r') as f:
            lines = f.readlines()

        orig_index = lines.index("Original AST:\n") + 1
        opt_index = lines.index("Optimized AST:\n") + 1

        orig_ast_text = ''.join(lines[orig_index:opt_index - 1])
        opt_ast_text = ''.join(lines[opt_index:])

        # Read original C code
        with open('input.c', 'r') as f:
            original_code = f.read()

        # Read regenerated C code
        with open('regenerated.c', 'r') as f:
            regenerated_code = f.read()

        return render_template('result.html',
                               original_ast_text=orig_ast_text,
                               optimized_ast_text=opt_ast_text,
                               original_code=original_code,
                               regenerated_code=regenerated_code)
    except Exception as e:
        return f"Error displaying result: {e}"
@app.route('/images/<filename>')
def get_image(filename):
    return send_from_directory(app.config['UPLOAD_FOLDER'], filename)

if __name__ == '__main__':
    app.run(debug=True)