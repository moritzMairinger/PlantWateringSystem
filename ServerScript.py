from http.server import BaseHTTPRequestHandler, HTTPServer

Request = None
MyFile = None
counter = 0

class RequestHandler_httpd(BaseHTTPRequestHandler):
  def do_GET(self):
    global Request, MyFile
    messagetosend = bytes('Welcome!',"utf")
    self.send_response(200)
    self.send_header('Content-Type', 'text/plain')
    self.send_header('Content-Length', len(messagetosend))
    self.end_headers()
    self.wfile.write(messagetosend)
    Request = self.requestline
    Request = Request[5 : int(len(Request)-9)]
    print('Your request is: ')
    print(Request)
    MyFile = open('data.csv','a')
    #MyFile.write((''.join([str(x) for x in ['DATA;', Request, ';\n']])))
    MyFile.write(counter, ';', Request, ';\n')
    MyFile.close()
    return


print('Starting Server')
server_address_httpd = ('192.168.0.172',8080)
httpd = HTTPServer(server_address_httpd, RequestHandler_httpd)
httpd.serve_forever()