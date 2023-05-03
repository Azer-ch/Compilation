from flask import Flask , render_template, request
import subprocess

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')
@app.route('/compile' , methods = ['POST'])
def compile():
    code = request.form['code']
    compile = 'GUI/miniJavaCompiler'
    output_data_err = subprocess.run([compile],input=code.encode(),stderr=subprocess.PIPE).stderr.decode()
    output_data_err = output_data_err.replace(' ', '&nbsp;').replace('\n', '<br>');
    output_data_suc = subprocess.run([compile],input=code.encode(),stdout=subprocess.PIPE).stdout.decode()
    output_data_suc = output_data_suc.replace(' ', '&nbsp;').replace('\n', '<br>');
    return render_template('index.html',compiler_output_err = output_data_err,compiler_output_suc=output_data_suc, input_code = code)
if __name__ == '__main__':
    app.run(debug= True , use_reloader = True)