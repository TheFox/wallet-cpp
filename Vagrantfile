# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure('2') do |config|
  config.vm.box = 'generic/debian9'
  config.vm.box_check_update = false

  config.vm.hostname = 'wallet'

  config.vm.synced_folder '.', '/app'

  config.vm.provider 'virtualbox' do |vb|
    vb.gui = false
    vb.memory = 1024
  end

  config.vm.provision 'shell' do |s|
    s.env = {
      'DEBIAN_FRONTEND' => 'noninteractive',
      'WORKING_DIR' => '/app',
      'BASHRC_FILE' => '/home/vagrant/.bashrc',
      'TESTING_SOURCES_LIST' => '/etc/apt/sources.list.d/testing.list',
    }
    s.inline = <<-SHELL
      echo "cd ${WORKING_DIR}" >> ${BASHRC_FILE}
      echo "alias ll='ls -la'" >> ${BASHRC_FILE}
      echo "alias l='ls -l'" >> ${BASHRC_FILE}

      apt-get update -yqq
      apt-get upgrade -y
      apt-get install -y coreutils htop vim ack-grep lsof net-tools rsync

      echo "deb http://ftp.at.debian.org/debian/ testing main contrib non-free" >> ${TESTING_SOURCES_LIST}
      echo "deb-src http://ftp.at.debian.org/debian/ testing main contrib non-free" >> ${TESTING_SOURCES_LIST}
      apt-get update -yqq
      #apt-get install -y cmake clang-7 libboost-filesystem1.67-dev

      echo 'done'
    SHELL
  end
end
