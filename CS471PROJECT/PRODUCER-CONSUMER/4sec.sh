# Shell Script to run ProducerConsumer using a 4 second wait time.
# Outputs all data to a file 4sec-output.txt

./PRODUCER-CONSUMER/ProducerConsumer 4 1 1 > PRODUCER-CONSUMER/4sec-output.txt
./PRODUCER-CONSUMER/ProducerConsumer 4 1 4 >> PRODUCER-CONSUMER/4sec-output.txt
./PRODUCER-CONSUMER/ProducerConsumer 4 1 16 >> PRODUCER-CONSUMER/4sec-output.txt
./PRODUCER-CONSUMER/ProducerConsumer 4 4 1 >> PRODUCER-CONSUMER/4sec-output.txt
./PRODUCER-CONSUMER/ProducerConsumer 4 4 4 >> PRODUCER-CONSUMER/4sec-output.txt
./PRODUCER-CONSUMER/ProducerConsumer 4 4 16 >> PRODUCER-CONSUMER/4sec-output.txt
./PRODUCER-CONSUMER/ProducerConsumer 4 16 1 >> PRODUCER-CONSUMER/4sec-output.txt
./PRODUCER-CONSUMER/ProducerConsumer 4 16 4 >> PRODUCER-CONSUMER/4sec-output.txt
./PRODUCER-CONSUMER/ProducerConsumer 4 16 16 >> PRODUCER-CONSUMER/4sec-output.txt