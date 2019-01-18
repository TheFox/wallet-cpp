# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure('2') do |config|
  config.vm.box = 'generic/debian9'
  config.vm.box_check_update = false

  config.vm.hostname = 'wallet'

  config.vm.synced_folder '.', '/app/walletcpp'

  config.vm.provider 'virtualbox' do |vb|
    vb.gui = false
    vb.memory = 1024
  end

  config.vm.provision 'shell' do |s|
    s.env = {
      'DEBIAN_FRONTEND' => 'noninteractive',
      'WORKING_DIR' => '/app/walletcpp',
      'BASHRC_FILE' => '/home/vagrant/.bashrc',
      'BACKPORTS_SOURCES_LIST' => '/etc/apt/sources.list.d/backports.list',
    }
    s.inline = <<-SHELL
      chmod 0777 /app

      echo "cd ${WORKING_DIR}" >> ${BASHRC_FILE}
      echo "alias ll='ls -la'" >> ${BASHRC_FILE}
      echo "alias l='ls -l'" >> ${BASHRC_FILE}
      echo "export DEBFULLNAME='Christian Mayer'" >> ${BASHRC_FILE}
      echo "export DEBEMAIL='christian@fox21.at'" >> ${BASHRC_FILE}

      ln -s -f /usr/share/zoneinfo/Europe/Vienna /etc/localtime
      echo "Europe/Vienna" > /etc/timezone
      dpkg-reconfigure -f ${DEBIAN_FRONTEND} tzdata

      apt-get update -yqq
      apt-get install -y --no-install-recommends coreutils htop vim ack-grep lsof net-tools rsync libdistro-info-perl devscripts dh-make dh-exec libyaml-cpp-dev libboost-filesystem-dev libboost-program-options-dev libboost-date-time-dev

      echo "deb http://ftp.debian.org/debian stretch-backports main" > ${BACKPORTS_SOURCES_LIST}
      apt-get update -yqq
      apt-get -t stretch-backports install -y --no-install-recommends cmake

      push /tmp
      git clone https://github.com/no1msd/mstch.git
      push mstch
      mkdir build
      push build
      cmake ..
      make
      make install
      popd
      popd
      popd

      cd ${WORKING_DIR}
      mkdir -p build_debian
      cd build_debian
      cmake ..
      make

      echo 'done'
    SHELL
  end
end
