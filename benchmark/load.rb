require 'open-uri'
open('image_00.jpg', 'wb') do |file|
	file << open('https://upload.wikimedia.org/wikipedia/commons/e/ed/02.Trinidad_(59).JPG').read
end
