require 'open-uri'
require 'rmagick'

open('image_00.jpg', 'wb') do |file|
	file << open('https://upload.wikimedia.org/wikipedia/commons/e/ed/02.Trinidad_(59).JPG').read
end

i = Magick::Image.read('image_00.jpg').first
i.write('image_00.png') do
	self.format = 'PNG'
end
